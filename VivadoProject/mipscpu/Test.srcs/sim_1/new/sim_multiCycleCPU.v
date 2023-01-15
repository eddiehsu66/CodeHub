`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/10/30 15:23:51
// Design Name: 
// Module Name: sim_multiCycleCPU
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


module sim_multiCycleCPU();
reg clk;
reg rst;
wire [31:0] instruction,readData1, readData2, DB, curPC,Result ,newPC;
multiCycleCPU sim(
clk,rst,instruction,readData1, readData2, DB, curPC,Result ,newPC
);

always
    #10 clk = ~clk; // 每隔 20ns 时钟信号 clk 翻转一次 
initial begin
    rst=0;
    clk=0;
    #30 rst = 1;
end
endmodule
