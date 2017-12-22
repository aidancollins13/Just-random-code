----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/08/2017 09:46:02 PM
-- Design Name: 
-- Module Name: FPGA - Behavioral
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity FPGA is
--  Port ( );
    Port(
    SW: in std_logic_vector(15 DOWNTO 0);
    middle: in std_logic;
    up: in std_logic;
    right: in std_logic;
    bottom: in std_logic;
    left: in std_logic;
    LED: out STD_LOGIC_VECTOR(15 DOWNTO 0);
    clk:in std_logic;
     seg 		: out  STD_LOGIC_VECTOR (7 downto 0);
     an         : out  STD_LOGIC_VECTOR (3 downto 0)
    );
end FPGA;

architecture Behavioral of FPGA is

component top is
Port ( 
    top_din: in std_logic_vector(63 DOWNTO 0);
    key: in std_logic_vector(127 DOWNTO 0);
    enc_dec: in std_logic;
    dout: out std_logic_vector(63 DOWNTO 0);
    start:in std_logic;
    done: out std_logic;
    clr:in std_logic;
    clk: in std_logic);
end component;


component Hex2LED --Converts a 4 bit hex value into the pattern to be displayed on the 7seg
port (CLK: in STD_LOGIC; X: in STD_LOGIC_VECTOR (3 downto 0); Y: out STD_LOGIC_VECTOR (7 downto 0)); 
end component; 

type arr is array(0 to 22) of std_logic_vector(7 downto 0);
signal NAME: arr;
signal Val : std_logic_vector(3 downto 0) := (others => '0');
signal HexVal: std_logic_vector(15 downto 0):=(others=>'0');
signal slowCLK,top_clk: std_logic:='0';
signal i_cnt: std_logic_vector(19 downto 0):=x"00000";
signal fpga_din: std_logic_vector(63 DOWNTO 0):=(OTHERS=>'0');
signal fpga_key: std_logic_vector(127 DOWNTO 0):=(OTHERS=>'0');
signal fpga_dout: std_logic_vector(63 DOWNTO 0);
signal fpga_enc_dec: std_logic;
signal fpga_done,fpga_clr: std_logic;
signal start: std_logic;
begin
-----Creating a slowCLK of 500Hz using the board's 100MHz clock----
process(CLK)
begin
if (rising_edge(CLK)) then
    if (i_cnt=x"186A0")then --Hex(186A0)=Dec(100,000)
        slowCLK<=not slowCLK; --slowCLK toggles once after we see 100000 rising edges of CLK. 2 toggles is one period.
        i_cnt<=x"00000";
else
    i_cnt<=i_cnt+'1';
end if;
end if;
end process;

-----We use the 500Hz slowCLK to run our 7seg display at roughly 60Hz-----
timer_inc_process : process (slowCLK)
begin
	if (rising_edge(slowCLK)) then
				if(Val="0100") then
				Val<="0001";
				else
				Val <= Val + '1'; --Val runs from 1,2,3,...8 on every rising edge of slowCLK
			end if;
		end if;
end process;

--This select statement selects one of the 7-segment diplay anode(active low) at a time. 
with Val select
	an <= "0111" when "0001",
				  "1011" when "0010",
				  "1101" when "0011",
				  "1110" when "0100",
				  "1111" when others;

--This select statement selects the value of HexVal to the necessary
--cathode signals to display it on the 7-segment
with Val select
	seg <= NAME(0) when "0001", --NAME contains the pattern for each hex value to be displayed.
				  NAME(1) when "0010", --See below for the conversion
				  NAME(2) when "0011",
				  NAME(3) when "0100",
				  NAME(0) when others;

--HexVal<=x"0000";
--Trying to display ABCD on the 7segment display by first sending it to 
--Hex2LED for converting each Hex value to a pattern to be given to the cathode.

process(up,bottom,left,right,middle,top_clk,fpga_dout,fpga_done)
begin
    if(top_clk'EVENT and top_clk='1') then
        if(up = '1') then
            fpga_din(31 DOWNTO 16) <= SW;
            if(fpga_done = '1') then LED<=fpga_dout(63 DOWNTO 48); 
                HExVal<=fpga_dout(63 DOWNTO 48);
                end if;
        elsif(right = '1') then
		    fpga_din(15 DOWNTO 0) <= SW;
		    if(fpga_done='1') then LED<=fpga_dout(47 DOWNTO 32); 
		      HExVal<=fpga_dout(47 DOWNTO 32);
		      end if;
		elsif(bottom = '1') then
		    fpga_key(15 DOWNTO 0) <= SW;
		    if(fpga_done='1') then LED<=fpga_dout(15 DOWNTO 0); 
		      HExVal<=fpga_dout(15 DOWNTO 0); 
		      end if;
		elsif(left = '1') then
		    fpga_key(31 DOWNTO 16) <= SW;
		    if(fpga_done='1') then LED<=fpga_dout(31 DOWNTO 16); 
		      HexVal<=fpga_dout(31 DOWNTO 16); 
		      end if;
		elsif(middle = '1') THEN
		     fpga_enc_dec<=SW(0);
		     fpga_clr<=SW(1);
		     start<=SW(2);
		     LED(0) <= fpga_done;
		end if;
	end if;
end process;

--HExVal <= fpga_dout(63 DOWNTO 48);

--WITH SW select
--    HexVal<=fpga_dout(63 DOWNTO 48) when X"0008",
--        fpga_dout(47 DOWNTO 32) when X"0004",
--        fpga_dout(31 DOWNTO 16) when X"0002",
--        fpga_dout(15 DOWNTO 0) when X"0001",
--    x"0000" when others;

process(clk)
begin
    if(clk'EVENt and clk ='1') then
        top_clk<=not top_clk;
     end if;
end process;
--process(fpga_done)
--begin
--    if(fpga_done = '1') then
--        fpga_dout<=dout_reg;
--    end if;
--end process;


t1: top port map(top_din=>fpga_din, key=>fpga_key, enc_dec=>fpga_enc_dec, dout=>fpga_dout, start=>start, done=>fpga_done, clr=>fpga_clr, clk=>top_clk); 
CONV5: Hex2LED port map (CLK => CLK, X => HexVal(15 downto 12), Y => NAME(0));
CONV6: Hex2LED port map (CLK => CLK, X => HexVal(11 downto 8), Y => NAME(1));
CONV7: Hex2LED port map (CLK => CLK, X => HexVal(7 downto 4), Y => NAME(2));
CONV8: Hex2LED port map (CLK => CLK, X => HexVal(3 downto 0), Y => NAME(3));



end Behavioral;