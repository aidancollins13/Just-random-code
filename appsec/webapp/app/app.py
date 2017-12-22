from flask import Flask, render_template, request
import os
import imghdr
import time

#these are settings for flask

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = './static'
app.config['MAX_CONTENT_PATH'] = 10000000
app.secret_key = 'appsec'

class image(object):
    def __init__(self, name, caption):
        self.name = name
        self.caption = caption

def secure_image(image, caption):
    ftype =  imghdr.what(image)
    if(ftype == 'jpg' or ftype == 'png' or ftype == 'gif') and len(caption) <= 140:
        return True
    return False


# this functoin takes in the name of that image and writes it to a file which
# keeps track of the images
def save_image(image_name, caption):
    f = open("image_list", 'a+')
    f.write(image_name)
    f.write(":")
    f.write(caption)
    f.write("\n")
    f.close();

#this function will read the image list file and return an array to the 10 most recent images

def get_images():
    image_list = []
    try:
        f = open("image_list", 'r')
        for line in f:
            i = line.split(':')
            name = os.path.join(app.config['UPLOAD_FOLDER'], i[0])
            caption = i[1]
            image_list.append(image(name,caption))
        f.close()
    except:
        image_list.append(image('no image', 'no image'))

    return (image_list[:10])[::-1]

# this is the code for the homepage, it reders index.html and gives it an
# variable called images that has the 10 most recent images
@app.route('/')
def index():
    return render_template('index.html', images=get_images())

# this is the code for /uploader this simply renders uploader.html
@app.route('/uploader')
def uploader():
    return render_template('uploader.html')
# this is the page that uploader redirects too
# this gets the fils uploaded to the wepage, saves it in the upload folser, and
# calls save_image to keep track of the image
@app.route('/upload', methods=['GET', 'POST'])
def upload():
    if request.method == 'POST':
        i = request.files['file'] # this is how flask processes files
        c = request.form['caption']
        if(secure_image(i,c)):
            image_name = str(time.clock()) + ".jpg"
            i.save(os.path.join(app.config['UPLOAD_FOLDER'], image_name)) # this saves the image as the given filename in the upload folder
            save_image(image_name, c)
            return render_template("upload.html", c=c)
        else:
           return  "invalid image/caption"

if __name__ == '__main__': # this enables debugging if app.py is run as python2 app.py as apposed to falsk run
    app.run(debug = True)




