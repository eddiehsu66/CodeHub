`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/10/23 16:51:09
// Design Name: 
// Module Name: instructionMemory
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


module instructionMemory(
    input [31:0] pc,   
    output [31:0] instruction
    );
    
    reg [7:0] mem[0:127];
    reg [31:0] address;
    reg [31:0] instruction;
    initial begin
        $readmemb("C:/code/hub/vivado_pro/Test/test2.txt", mem); 
        //C:/code/hub/vivado_pro/Test/Test.txt
    end
    
    always @(pc) begin //��ȡָ��
        address = pc[6:2] << 2; 
        instruction = (mem[address]<<24) + (mem[address+1]<<16) + (mem[address+2]<<8) + mem[address+3];
    end

    
endmodule
