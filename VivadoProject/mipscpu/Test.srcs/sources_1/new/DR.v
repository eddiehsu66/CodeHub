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

//DRֻ������һ������������ǿ���������ͳ�����
module DR(
    input clk,
    input [31:0] in,
    output reg [31:0] out
    );
    //ʱ��������ʱ�������ͳ�
    always @(posedge clk) begin
        out = in;
    end
endmodule
