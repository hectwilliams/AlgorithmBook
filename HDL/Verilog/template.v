module (a_o, b_o, clk_i, a_i, b_i, c_i)
  // Module I/O
  input clk_i;
  input a_i, b_i;
  input [7:0] c_i;
  output a_o;
  output reg [7:0] b_o; // reg persists value

  parameter dead_beef = 32'hDEAD_BEEF
  localparam ONE = 4'b0001;
  localparam TWO = 4'b0010;
  reg [31:0] name = "Magneto";

endmodule