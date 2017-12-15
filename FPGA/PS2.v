module Keyboard(
	input clk25,
	input PS2C,
	input PS2D,
	output reg [7:0] ascii
	);

	reg PS2Cf, PS2Df;
	reg [7:0] ps2c_filter, ps2d_filter;
	reg [10:0] shift1, shift2;
	reg [7:0] pre;
	reg [31:0] anti_jetter;
	
	reg shift, ctrl, alt;
	reg capslock, numlock;

	always @(posedge clk25)// 取值防干扰，参考书上，不做赘述
	begin
		ps2c_filter[7] <= PS2C;
		ps2c_filter[6:0] <= ps2c_filter[7:1];
		ps2d_filter[7] <= PS2D;
		ps2d_filter[6:0] <= ps2d_filter[7:1];
		if (ps2c_filter == 8'b11111111)
		begin
			PS2Cf <= 1;
		end
		else
		if (ps2c_filter == 8'b00000000)
		begin
			PS2Cf <= 0;
		end
		if (ps2d_filter == 8'b11111111)
		begin
			PS2Df <= 1;
		end
		else
		if (ps2d_filter == 8'b00000000)
		begin
			PS2Df <= 0;
		end
	end

	always @(negedge PS2Cf)
	begin
		shift1 <= {PS2Df, shift1[10:1]};
		shift2 <= {shift1[0], shift2[10:1]};
	end
	
	always @(posedge clk25) begin
		if (shift2[8:1] != 8'hF0)
			pre[7:0] <= shift1[8:1];
		if (shift2[8:1] == 8'hF0)
			pre[7:0] <= 8'h00;
		if(pre!=ascii)
			anti_jetter = anti_jetter + 1;
		else
			anti_jetter = 8'b0;
		
	end
	
	always@(posedge anti_jetter[17])begin
		if(shift == 1'b0)begin
			case(pre[7:0])
			8'h00: begin
				ascii[7:0] <= 8'h00; // none
				shift <= 1'b0;
				ctrl <= 1'b0;
				alt <= 1'b0;
			end
			8'h1c: ascii[7:0] <= 8'h61; // a
			8'h32: ascii[7:0] <= 8'h62; // b
			8'h21: ascii[7:0] <= 8'h63; // c
			8'h23: ascii[7:0] <= 8'h64; // d
			8'h24: ascii[7:0] <= 8'h65; // e
			8'h2b: ascii[7:0] <= 8'h66; // f
			8'h34: ascii[7:0] <= 8'h67; // g
			8'h33: ascii[7:0] <= 8'h68; // h
			8'h43: ascii[7:0] <= 8'h69; // i
			8'h3b: ascii[7:0] <= 8'h6A; // j
			8'h42: ascii[7:0] <= 8'h6B; // k
			8'h4b: ascii[7:0] <= 8'h6C; // l
			8'h3a: ascii[7:0] <= 8'h6D; // m
			8'h31: ascii[7:0] <= 8'h6E; // n
			8'h44: ascii[7:0] <= 8'h6F; // o
			8'h4d: ascii[7:0] <= 8'h70; // p
			8'h15: ascii[7:0] <= 8'h71; // q
			8'h2d: ascii[7:0] <= 8'h72; // r
			8'h1b: ascii[7:0] <= 8'h73; // s
			8'h2c: ascii[7:0] <= 8'h74; // t
			8'h3c: ascii[7:0] <= 8'h75; // u
			8'h2a: ascii[7:0] <= 8'h76; // v
			8'h1d: ascii[7:0] <= 8'h77; // w
			8'h22: ascii[7:0] <= 8'h78; // x
			8'h35: ascii[7:0] <= 8'h79; // y
			8'h1a: ascii[7:0] <= 8'h7A; // z
			8'h45: ascii[7:0] <= 8'h30; // 0
			8'h16: ascii[7:0] <= 8'h31; // 1
			8'h1e: ascii[7:0] <= 8'h32; // 2
			8'h26: ascii[7:0] <= 8'h33; // 3
			8'h25: ascii[7:0] <= 8'h34; // 4
			8'h2e: ascii[7:0] <= 8'h35; // 5
			8'h36: ascii[7:0] <= 8'h36; // 6
			8'h3d: ascii[7:0] <= 8'h37; // 7
			8'h3e: ascii[7:0] <= 8'h38; // 8
			8'h46: ascii[7:0] <= 8'h39; // 9
			8'h29: ascii[7:0] <= 8'h20; // SPACE
			8'h66: ascii[7:0] <= 8'h08; // BKSP
			8'h5a: ascii[7:0] <= 8'h0D; // Enter
			8'h12: shift <= 1'b1;
			8'h59: shift <= 1'b1;
			8'h14: ctrl <= 1'b1;
			8'h11: alt <= 1'b1;
			endcase
		end
		else begin
			case(pre[7:0])
			8'h00: begin
				ascii[7:0] <= 8'h00; // none
				shift <= 1'b0;
				ctrl <= 1'b0;
				alt <= 1'b0;
			end
			8'h1c: ascii[7:0] <= 8'h41; // a
			8'h32: ascii[7:0] <= 8'h42; // b
			8'h21: ascii[7:0] <= 8'h43; // c
			8'h23: ascii[7:0] <= 8'h44; // d
			8'h24: ascii[7:0] <= 8'h45; // e
			8'h2b: ascii[7:0] <= 8'h46; // f
			8'h34: ascii[7:0] <= 8'h47; // g
			8'h33: ascii[7:0] <= 8'h48; // h
			8'h43: ascii[7:0] <= 8'h49; // i
			8'h3b: ascii[7:0] <= 8'h4A; // j
			8'h42: ascii[7:0] <= 8'h4B; // k
			8'h4b: ascii[7:0] <= 8'h4C; // l
			8'h3a: ascii[7:0] <= 8'h4D; // m
			8'h31: ascii[7:0] <= 8'h4E; // n
			8'h44: ascii[7:0] <= 8'h4F; // o
			8'h4d: ascii[7:0] <= 8'h50; // p
			8'h15: ascii[7:0] <= 8'h51; // q
			8'h2d: ascii[7:0] <= 8'h52; // r
			8'h1b: ascii[7:0] <= 8'h53; // s
			8'h2c: ascii[7:0] <= 8'h54; // t
			8'h3c: ascii[7:0] <= 8'h55; // u
			8'h2a: ascii[7:0] <= 8'h56; // v
			8'h1d: ascii[7:0] <= 8'h57; // w
			8'h22: ascii[7:0] <= 8'h58; // x
			8'h35: ascii[7:0] <= 8'h59; // y
			8'h1a: ascii[7:0] <= 8'h5A; // z
			8'h45: ascii[7:0] <= 8'h29; // 0
			8'h16: ascii[7:0] <= 8'h21; // 1
			8'h1e: ascii[7:0] <= 8'h40; // 2
			8'h26: ascii[7:0] <= 8'h23; // 3
			8'h25: ascii[7:0] <= 8'h24; // 4
			8'h2e: ascii[7:0] <= 8'h25; // 5
			8'h36: ascii[7:0] <= 8'h5E; // 6
			8'h3d: ascii[7:0] <= 8'h26; // 7
			8'h3e: ascii[7:0] <= 8'h2A; // 8
			8'h46: ascii[7:0] <= 8'h28; // 9
			8'h29: ascii[7:0] <= 8'h20; // SPACE
			8'h66: ascii[7:0] <= 8'h08; // BKSP
			8'h5a: ascii[7:0] <= 8'h0D; // Enter
			8'h12: shift <= 1'b1;
			8'h59: shift <= 1'b1;
			8'h14: ctrl <= 1'b1;
			8'h11: alt <= 1'b1;
			endcase
		end
	end

endmodule