----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/10/2017 10:49:42 AM
-- Design Name: 
-- Module Name: state_decryption - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use work.srom.all;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity state_decryption is
--  Port ( );
 PORT  (
   skey: in rom;
   clr: IN STD_LOGIC;  -- asynchronous reset
   clk: IN STD_LOGIC;  -- Clock signal
   start: IN STD_LOGIC;
   done: OUT STD_LOGIC;
   din: IN STD_LOGIC_VECTOR(63 DOWNTO 0);--64-bit i/p
   dout: OUT STD_LOGIC_VECTOR(63 DOWNTO 0)--64-bit o/p
   );

end state_decryption;

architecture Behavioral of state_decryption is
    
    SIGNAL b: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL a: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL b_reg: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL a_reg: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL bs: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL as: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL i_cnt: STD_LOGIC_VECTOR(3 DOWNTO 0);  
    SIGNAL bs_rot: STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL as_rot: STD_LOGIC_VECTOR(31 DOWNTO 0);


    --TYPE rom IS ARRAY (0 TO 25) OF STD_LOGIC_VECTOR(31 DOWNTO 0); 
    
      --CONSTANT skey: rom:=rom'(X"9BBBD8C8", X"1A37F7FB", X"46F8E8C5", X"460C6085", 
    --X"70F83B8A", X"284B8303", X"513E1454", X"F621ED22", 
    --X"3125065D", X"11A83A5D", X"D427686B", X"713AD82D", 
    --X"4B792F99", X"2799A4DD", X"A7901C49", X"DEDE871A", 
    --X"36C03196", X"A7EFC249", X"61A78BB8", X"3B0A1D2B", 
    --X"4DBFCA76", X"AE162167", X"30D76B0A", X"43192304", 
    --X"F6CC1431", X"65046380");
    
     TYPE     StateType IS (ST_IDLE, ST_LAST, ST_KEY_EXP, ST_READY);
      SIGNAL    state : StateType;

    
begin

PROCESS(clr, clk)
BEGIN
       IF(clr='0') THEN
           state<=ST_IDLE;
       ELSIF(clk'EVENT AND clk='1') THEN
           CASE state IS
              WHEN ST_IDLE => 
                IF(start='1') THEN  state<=ST_KEY_EXP;   END IF;
                i_cnt <= "1100";
                a_reg <= din(63 DOWNTO 32);
                b_reg <= din(31 DOWNTO 0);
                done<='0';
		             
              WHEN ST_KEY_EXP=> 
		        IF(i_cnt="0001") THEN   state<=ST_LAST;
		        else
		           i_cnt <= i_cnt-1;
		        END IF;
		        a_reg<= a;
                b_reg<=b;
              WHEN ST_LAST=>
                STATE <= ST_READY;
                b_reg <= b_reg - skey(1);
                a_reg <= a_reg - skey(0);
                done<='1';
                
              WHEN ST_READY=>
              if(clr='0') THEN
                state<=ST_IDLE;
              end if;
                
          END CASE;
        END IF;
END PROCESS;
    

          
    bs <= b_reg - skey(CONV_INTEGER(i_cnt & '1'));
    as <= a_reg - skey(CONV_INTEGER(i_cnt & '0'));
    
    with a_reg(4 DOWNTO 0) SELECT
        bs_rot<= bs(0) & bs(31 DOWNTO 1) when "00001",
        bs(1 DOWNTO 0) & bs(31 DOWNTO 2) when "00010",
        bs(2 DOWNTO 0) & bs(31 DOWNTO 3) when "00011",
        bs(3 DOWNTO 0)& bs(31 DOWNTO 4) when "00100",
        bs(4 DOWNTO 0) & bs(31 DOWNTO 5) when "00101",
        bs(5 DOWNTO 0) & bs(31 DOWNTO 6) when "00110",
        bs(6 DOWNTO 0) & bs(31 DOWNTO 7) when "00111",
        bs(7 DOWNTO 0) & bs(31 DOWNTO 8) when "01000",
        bs(8 DOWNTO 0) & bs(31 DOWNTO 9) when "01001",
        bs(9 DOWNTO 0) & bs(31 DOWNTO 10) when "01010",
        bs(10 DOWNTO 0) & bs(31 DOWNTO 11) when "01011",
        bs(11 DOWNTO 0) & bs(31 DOWNTO 12) when "01100",
        bs(12 DOWNTO 0) & bs(31 DOWNTO 13) when "01101",
        bs(13 DOWNTO 0) & bs(31 DOWNTO 14) when "01110",
        bs(14 DOWNTO 0) & bs(31 DOWNTO 15) when "01111",
        bs(15 DOWNTO 0) & bs(31 DOWNTO 16) when "10000",
        bs(16 DOWNTO 0) & bs(31 DOWNTO 17) when "10001",
        bs(17 DOWNTO 0) & bs(31 DOWNTO 18) when "10010",
        bs(18 DOWNTO 0) & bs(31 DOWNTO 19) when "10011",
        bs(19 DOWNTO 0) & bs(31 DOWNTO 20) when "10100",
        bs(20 DOWNTO 0) & bs(31 DOWNTO 21) when "10101",
        bs(21 DOWNTO 0) & bs(31 DOWNTO 22) when "10110",
        bs(22 DOWNTO 0) & bs(31 DOWNTO 23) when "10111",
        bs(23 DOWNTO 0) & bs(31 DOWNTO 24) when "11000",
        bs(24 DOWNTO 0) & bs(31 DOWNTO 25) when "11001",
        bs(25 DOWNTO 0) & bs(31 DOWNTO 26) when "11010",
        bs(26 DOWNTO 0) & bs(31 DOWNTO 27) when "11011",
        bs(27 DOWNTO 0) & bs(31 DOWNTO 28) when "11100",
        bs(28 DOWNTO 0) & bs(31 DOWNTO 29) when "11101",
        bs(29 DOWNTO 0) & bs(31 DOWNTO 30) when "11110",
        bs(30 DOWNTO 0) & bs(31) when "11111",
        bs when OTHERS; 

        b <= bs_rot XOR a_reg;
        
    WITH b(4 DOWNTO 0) SELECT
       as_rot<= as(0) & as(31 DOWNTO 1) when "00001",
            as(1 DOWNTO 0) & as(31 DOWNTO 2) when "00010",
            as(2 DOWNTO 0) & as(31 DOWNTO 3) when "00011",
            as(3 DOWNTO 0)& as(31 DOWNTO 4) when "00100",
            as(4 DOWNTO 0) & as(31 DOWNTO 5) when "00101",
            as(5 DOWNTO 0) & as(31 DOWNTO 6) when "00110",
            as(6 DOWNTO 0) & as(31 DOWNTO 7) when "00111",
            as(7 DOWNTO 0) & as(31 DOWNTO 8) when "01000",
            as(8 DOWNTO 0) & as(31 DOWNTO 9) when "01001",
            as(9 DOWNTO 0) & as(31 DOWNTO 10) when "01010",
            as(10 DOWNTO 0) & as(31 DOWNTO 11) when "01011",
            as(11 DOWNTO 0) & as(31 DOWNTO 12) when "01100",
            as(12 DOWNTO 0) & as(31 DOWNTO 13) when "01101",
            as(13 DOWNTO 0) & as(31 DOWNTO 14) when "01110",
            as(14 DOWNTO 0) & as(31 DOWNTO 15) when "01111",
            as(15 DOWNTO 0) & as(31 DOWNTO 16) when "10000",
            as(16 DOWNTO 0) & as(31 DOWNTO 17) when "10001",
            as(17 DOWNTO 0) & as(31 DOWNTO 18) when "10010",
            as(18 DOWNTO 0) & as(31 DOWNTO 19) when "10011",
            as(19 DOWNTO 0) & as(31 DOWNTO 20) when "10100",
            as(20 DOWNTO 0) & as(31 DOWNTO 21) when "10101",
            as(21 DOWNTO 0) & as(31 DOWNTO 22) when "10110",
            as(22 DOWNTO 0) & as(31 DOWNTO 23) when "10111",
            as(23 DOWNTO 0) & as(31 DOWNTO 24) when "11000",
            as(24 DOWNTO 0) & as(31 DOWNTO 25) when "11001",
            as(25 DOWNTO 0) & as(31 DOWNTO 26) when "11010",
            as(26 DOWNTO 0) & as(31 DOWNTO 27) when "11011",
            as(27 DOWNTO 0) & as(31 DOWNTO 28) when "11100",
            as(28 DOWNTO 0) & as(31 DOWNTO 29) when "11101",
            as(29 DOWNTO 0) & as(31 DOWNTO 30) when "11110",
            as(30 DOWNTO 0) & as(31) when "11111",
            as when OTHERS; 
            
        a <= as_rot XOR b;
         
        dout <= a_reg & b_reg when state = ST_READY else a & b ;  
        

        
    
end Behavioral;

