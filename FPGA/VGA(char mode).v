`timescale 1ns / 1ps

//The logic outside should be:
//With the output addr, give this module the right character color and ascii code.

//Example:
//VGA vga(.d_in(ch), .addr(addr), others omitted);
//if(addr[5:0]==6'b1 && addr[12:6]==7'b1)d_in<=20'b1111_1111_1111_0110_0001;
//This means putting a white character 'a' at position(1, 1).

module VGA (
	input clk, //Clock cycle must be 25mhz.
	input rst, //VGA reset at positive edge of rst.
	input [19:0] d_in, //Values rrrr_gggg_bbbb_ascii, the color and ascii of the current character.
	
	output reg [3:0] r, //The VGA red channel.
	output reg [3:0] g, //The VGA green channel.
	output reg [3:0] b, //The VGA blue channel.
	output reg hs, //The VGA HSYNC bit.
	output reg vs, //The VGA VSYNC bit.
	output [12:0] addr //Current pixel position (x = addr[12:6], y = addr[5:0])
	);
	
	wire [9:0] row, col;
	wire [7:0] font_ascii;
	wire [3:0] font_line;
	wire [7:0] font_out;
	
	reg rdn;
	reg [9:0] h_count; // VGA horizontal counter (0-799): pixels
	reg [9:0] v_count; // VGA vertical counter (0-524): lines
	
	FONT FT(.ascii(font_ascii), .line(font_line), .out(font_out));
	
	always @ (posedge clk) begin
		if (rst) begin
			h_count <= 10'h0;
		end else if (h_count == 10'd799) begin
			h_count <= 10'h0;
		end else begin 
			h_count <= h_count + 10'h1;
		end
	end
	
	always @ (posedge clk or posedge rst) begin
		if (rst) begin
			v_count <= 10'h0;
		end else if (h_count == 10'd799) begin
			if (v_count == 10'd524) begin
				v_count <= 10'h0;
			end else begin
				v_count <= v_count + 10'h1;
			end
		end
	end
	
	assign row    =  v_count - 10'd35;     //pixel ram row addr 
	assign col    =  h_count - 10'd143;    //pixel ram col addr 
	wire h_sync = (h_count > 10'd95);    //96 -> 799
	wire v_sync = (v_count > 10'd1);     //2 -> 524
	wire read   = (h_count > 10'd142) &&
		(h_count < 10'd783) &&
		(v_count > 10'd34) &&
		(v_count < 10'd515);
    
	assign addr = rdn ? 13'h0 : {col[9:3], row[8:3]};
	assign font_ascii = rdn ? 8'b0 : d_in[7:0];
	assign font_line = {5'b0, row[2:0]};
	
	reg show_bit;
	always @ (posedge clk) begin
		rdn <= ~read;
		hs <= h_sync;
		vs <= v_sync;
		case(col[2:0])
		3'h0:show_bit <= font_out[7];
		3'h1:show_bit <= font_out[6];
		3'h2:show_bit <= font_out[5];
		3'h3:show_bit <= font_out[4];
		3'h4:show_bit <= font_out[3];
		3'h5:show_bit <= font_out[2];
		3'h6:show_bit <= font_out[1];
		3'h7:show_bit <= font_out[0];
		endcase
		
		r <= rdn ? 4'h0 : (show_bit ? d_in[19:16] : 4'b0000); // 4-bit red
		g <= rdn ? 4'h0 : (show_bit ? d_in[15:12] : 4'b0000); // 4-bit green
		b <= rdn ? 4'h0 : (show_bit ? d_in[11:8] : 4'b0000); // 4-bit blue
	end
endmodule
