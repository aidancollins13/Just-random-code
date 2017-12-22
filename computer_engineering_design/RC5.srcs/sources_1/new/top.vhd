----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/01/2017 10:33:12 AM
-- Design Name: 
-- Module Name: top - Behavioral
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
use work.srom.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top is
Port ( 
    top_din: in std_logic_vector(63 DOWNTO 0);
    key: in std_logic_vector(127 DOWNTO 0);
    enc_dec: in std_logic;
    dout: out std_logic_vector(63 DOWNTO 0);
    start:in std_logic;
    done: out std_logic;
    clr:in std_logic;
    clk: in std_logic);
end top;

architecture Behavioral of top is
component state_encryption
PORT    (din: in STD_LOGIC_VECTOR(63 DOWNTO 0);
         skey: in rom;
         clk: IN STD_lOGIC ;
         clr: IN STD_LOGIC;
         start: IN STD_LOGIC; 
         done: OUT STD_LOGIC;
         dout:OUT std_logic_vector(63 downto 0) );
end component;

component state_decryption
PORT    (din: in STD_LOGIC_VECTOR(63 DOWNTO 0);
         skey: in rom;
         clk: IN STD_lOGIC ;
         clr: IN STD_LOGIC;
         start: IN STD_LOGIC; 
         done: OUT STD_LOGIC;
         dout:OUT std_logic_vector(63 downto 0) );
end component;

component round_keygen
PORT (
        clr,clk : in STD_LOGIC;
        key_in: in STD_LOGIC;
        ukey: in STD_LOGIC_VECTOR(127 DOWNTO 0);
        skey: out rom;
        key_rdy: out STD_LOGIC);
end component;

  
  SIGNAL key_done,enc_done,dec_done: std_logic;
  SIGNAL ukey: std_logic_vector(127 DOWNTO 0);
  SIGNAL enc_dout, dec_dout: std_logic_vector(63 DOWNTO 0);
  SIGNAL skey_out: rom;
  signal stop_enc:std_logic:=clr;
begin
    U1:round_keygen port map(clr=>clr, clk=>clk, key_in=>start, ukey=>key, skey=>skey_out, key_rdy=>key_done);
    U2: state_encryption port map(skey=>skey_out, clr=>stop_enc, clk=>clk, start=>key_done, done=>enc_done, din=>top_din, dout=>enc_dout);
    U3: state_decryption port map(skey=>skey_out, clr=>stop_enc, clk=>clk, start=>key_done, done=>dec_done, din=>top_din, dout=>dec_dout);

 
  
  
  with enc_dec select
    dout<= enc_dout when '1',
    dec_dout when others;
    
  with enc_dec select
    done<=enc_done when '1',
    dec_done when others;
    


end Behavioral;
