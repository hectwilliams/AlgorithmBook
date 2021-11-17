library ieee;
use ieee.std_logic_logic_1164.all;
use ieee.numeric_std.all;  -- signed, function '+', integer
use ieee.std_logic_textio.all; -- rd/wr std_logic_vector types
use std.textio.all; -- rd/wr other types

entity template is
generic (
  iteration_count: integer := 3;
  name: string := "Magneto"
);
port
(
  clk_i: std_logic;
  a_i: std_logic;
  b_i: std_logic;
  c_i: std_logic_vector(7 downto 0) := (others => '0')
  a_o: std_logic;
  b_o: std_logic_vector(7 downto 0)
);

constant ONE : std_logic_vector(3 downto 0) := "0001";
constant TWO : std_logic_vector(3 downto 0) := "0010";
signal dead_beef : std_logic_vector(31 downto 0) := x"DEAD_BEEF";

end template;