----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/01/2017 10:18:03 AM
-- Design Name: 
-- Module Name: round_keygen - Behavioral
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
use IEEE.STD_LOGIC_unsigned.all;
use work.srom.all;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL; 

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity round_keygen is
    PORT (
        clr,clk : in STD_LOGIC;
        key_in: in STD_LOGIC;
        ukey: in STD_LOGIC_VECTOR(127 DOWNTO 0);
        skey: out rom;
        key_rdy: out STD_LOGIC);
end round_keygen;

architecture Behavioral of round_keygen is
    
    
    SIGNAL L: L_ARRAY;
    SIGNAL S :rom:=rom'( X"b7e15163", X"5618cb1c", X"f45044d5", X"9287be8e", X"30bf3847",
     X"cef6b200", X"6d2e2bb9", X"0b65a572", X"a99d1f2b", X"47d498e4", X"e60c129d", X"84438c56",
      X"227b060f", X"c0b27fc8", X"5ee9f981", X"fd21733a", X"9b58ecf3", X"399066ac", X"d7c7e065",
       X"75ff5a1e", X"1436d3d7", X"b26e4d90", X"50a5c749", X"eedd4102", X"8d14babb", X"2b4c3474"); 

      
      TYPE     StateType IS (ST_IDLE, ST_KEY_IN, ST_KEY_EXP, ST_READY);
      SIGNAL    state : StateType;
      signal i_cnt, j_cnt, x_cnt: INTEGER:=0;
      signal a_tmp1, a_tmp2, b_tmp1, b_tmp2, ab_tmp: STD_LOGIC_VECTOR(31 DOWNTO 0);
      signal a_reg, b_reg: STD_LOGIC_VECTOR(31 DOWNTO 0):=(OTHERS=>'0');
begin
    --L[0]<=ukey(31 DOWNTO 0);
    --L[1]<=ukey(63 DOWNTO 32);
    --L[2]<=ukey(95 DOWNTO 64);
    --L[3]<=ukey(127 DOWNTO 96);
    
     Process(clk,clr)
        BEGIN
            if(clr='0') THEN
                state<=ST_IDLE;
            elsif(clk'event and clk='1') THEN
                case state is
                    when ST_IDLE | ST_READY =>
                        key_rdy <= '0';
                        IF(key_in = '1') THEN state <= ST_KEY_IN; END IF;
                        x_cnt <= 0;
                    when ST_KEY_IN =>
                         state<=ST_KEY_EXP;
                    when ST_KEY_EXP => 
                        x_cnt <= x_cnt+1;
                        S(i_cnt) <= a_tmp2;
                        IF(x_cnt = 77) THEN state <= ST_READY; key_rdy <= '1';
                        end if;
                   end case;
            end if;
        end process;
    
    a_tmp1<=S(i_cnt)+a_reg+b_reg;
     -- <<<3
    a_tmp2<=a_tmp1(28 DOWNTO 0) & a_tmp1(31 DOWNTO 29);
    
    ab_tmp<=a_tmp2+b_reg;
    b_tmp1<=L(j_cnt) + ab_tmp;
    
    WITH ab_tmp(4 DOWNTO 0) SELECT
      b_tmp2<= 
       b_tmp1(30 DOWNTO 0) & b_tmp1(31)           WHEN "00001",
       b_tmp1(29 DOWNTO 0) & b_tmp1(31 DOWNTO 30) WHEN "00010",
       b_tmp1(28 DOWNTO 0) & b_tmp1(31 DOWNTO 29) WHEN "00011",
       b_tmp1(27 DOWNTO 0) & b_tmp1(31 DOWNTO 28) When "00100",
       b_tmp1(26 DOWNTO 0) & b_tmp1(31 DOWNTO 27) WHEN "00101",
       b_tmp1(25 DOWNTO 0) & b_tmp1(31 DOWNTO 26) WHEN "00110",
       b_tmp1(24 DOWNTO 0) & b_tmp1(31 DOWNTO 25) WHEN "00111",
       b_tmp1(23 DOWNTO 0) & b_tmp1(31 DOWNTO 24) WHEN "01000",
       b_tmp1(22 DOWNTO 0) & b_tmp1(31 DOWNTO 23) WHEN "01001",
       b_tmp1(21 DOWNTO 0) & b_tmp1(31 DOWNTO 22) WHEN "01010",
       b_tmp1(20 DOWNTO 0) & b_tmp1(31 DOWNTO 21) WHEN "01011",
       b_tmp1(19 DOWNTO 0) & b_tmp1(31 DOWNTO 20) WHEN "01100",
       b_tmp1(18 DOWNTO 0) & b_tmp1(31 DOWNTO 19) WHEN "01101",
       b_tmp1(17 DOWNTO 0) & b_tmp1(31 DOWNTO 18) when "01110",
       b_tmp1(16 DOWNTO 0) & b_tmp1(31 DOWNTO 17) when "01111",
       b_tmp1(15 DOWNTO 0) & b_tmp1(31 DOWNTO 16) when "10000",
       b_tmp1(14 DOWNTO 0) & b_tmp1(31 DOWNTO 15) when "10001",
       b_tmp1(13 DOWNTO 0) & b_tmp1(31 DOWNTO 14) when "10010",
       b_tmp1(12 DOWNTO 0) & b_tmp1(31 DOWNTO 13) when "10011",
       b_tmp1(11 DOWNTO 0) & b_tmp1(31 DOWNTO 12) when "10100",
       b_tmp1(10 DOWNTO 0) & b_tmp1(31 DOWNTO 11) when "10101",
       b_tmp1(9 DOWNTO 0) & b_tmp1(31 DOWNTO 10) when  "10110",
       b_tmp1(8 DOWNTO 0) & b_tmp1(31 DOWNTO 9) when   "10111",
       b_tmp1(7 DOWNTO 0) & b_tmp1(31 DOWNTO 8) when   "11000",
       b_tmp1(6 DOWNTO 0) & b_tmp1(31 DOWNTO 7) when   "11001",
       b_tmp1(5 DOWNTO 0) & b_tmp1(31 DOWNTO 6) when   "11010",
       b_tmp1(4 DOWNTO 0) & b_tmp1(31 DOWNTO 5) when   "11011",
       b_tmp1(3 DOWNTO 0) & b_tmp1(31 DOWNTO 4) when   "11100",
       b_tmp1(2 DOWNTO 0) & b_tmp1(31 DOWNTO 3)  when  "11101",
       b_tmp1(1 DOWNTO 0) & b_tmp1(31 DOWNTO 2) when   "11110",
       b_tmp1(0) & b_tmp1(31 DOWNTO 1)            WHEN "11111",
       b_tmp1                                WHEN OTHERS;

    
    process(clk,clr)
        BEGIN
            if(clr='0') THEN
                for i IN 0 to 3 LOOP
                    L(i)<=(OTHERS=>'0');
                 end LOOP;
            elsif(clk'EVENT and clk='1') THEN
                if(state=ST_KEY_IN) THEN
                    L(0)<=ukey(31 DOWNTO 0);
                    L(1)<=ukey(63 DOWNTO 32);
                    L(2)<=ukey(95 DOWNTO 64);
                    L(3)<=ukey(127 DOWNTO 96);
                elsif(state=ST_KEY_EXP)THEN
                    L(j_cnt)<=b_tmp2;
                end if;
            end if;
        end process;    
    
        PROCESS(clr, clk)
         BEGIN
            IF(clr='0') THEN  i_cnt<=0;
            ELSIF(clk'EVENT AND clk='1') THEN
               IF(state=ST_KEY_EXP) THEN
                 IF(i_cnt=25) THEN   i_cnt<=0;
                 ELSE   i_cnt<=i_cnt+1;
                 END IF;
               END IF;
            END IF;
         END PROCESS;

    PROCESS(clr, clk)
    BEGIN
        IF(clr='0') THEN  j_cnt<=0;
        ELSIF(clk'EVENT AND clk='1') THEN
          IF(state=ST_KEY_EXP) THEN
            IF(j_cnt=3) THEN   j_cnt<=0;
            ELSE   j_cnt<=j_cnt+1;
            END IF;
         END IF;
        END IF;
    END PROCESS;
    
    PROCESS(clr, clk)  BEGIN
            IF(clr='0') THEN
               a_reg<=(OTHERS=>'0');
            ELSIF(clk'EVENT AND clk='1') THEN
               IF(state=ST_KEY_EXP) THEN   a_reg<=a_tmp2;
                END IF;
            END IF;
        END PROCESS;


    PROCESS(clr, clk)  BEGIN
        IF(clr='0') THEN
           b_reg<=(OTHERS=>'0');
        ELSIF(clk'EVENT AND clk='1') THEN
           IF(state=ST_KEY_EXP) THEN   b_reg<=b_tmp2; 
           END IF;
        END IF;
    END PROCESS;   


        
    skey <= S when state = ST_READY;
end Behavioral;