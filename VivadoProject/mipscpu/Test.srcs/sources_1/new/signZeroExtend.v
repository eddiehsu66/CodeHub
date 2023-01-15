`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/10/23 16:57:15
// Design Name: 
// Module Name: signZeroExtend
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module signZeroExtend(
    input [15:0] immediate,
    input ExtSel,
    output [31:0] out
    );
    //Á¢¼´ÊýÍØÕ¹
    assign out[15:0] = immediate;
    assign out[31:16] = ExtSel? (immediate[15]? 16'hffff : 16'h0000) : 16'h0000;
endmodule
