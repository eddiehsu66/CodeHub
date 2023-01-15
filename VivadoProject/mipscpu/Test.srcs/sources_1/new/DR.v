`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/10/23 16:54:32
// Design Name: 
// Module Name: DR
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

//DR只是其了一个缓冲作用来强制上升沿送出数据
module DR(
    input clk,
    input [31:0] in,
    output reg [31:0] out
    );
    //时钟上升沿时将数据送出
    always @(posedge clk) begin
        out = in;
    end
endmodule
