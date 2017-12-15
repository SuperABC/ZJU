`timescale 1ns / 1ps

module FONT(
    input [7:0]ascii,
    input [3:0]line,
    output reg [7:0]out
    );

	wire [63:0] fontTable [0:127];
	
	assign fontTable[0] = 64'h0000_0000_0000_0000;
	assign fontTable[1] = 64'h7E81_A581_BD99_817E;
	assign fontTable[2] = 64'h7EFF_DBFF_C3E7_FF7E;
	assign fontTable[3] = 64'h6CFE_FEFE_7C38_1000;
	assign fontTable[4] = 64'h1038_7CFE_7C38_1000;
	assign fontTable[5] = 64'h386C_6CEE_C67C_387C;
	assign fontTable[6] = 64'h0010_387C_FE7C_387C;
	assign fontTable[7] = 64'h0000_183C_3C18_0000;
	assign fontTable[8] = 64'hFFFF_E7C3_C3E7_FFFF;
	assign fontTable[9] = 64'h003C_6642_4266_3C00;
	assign fontTable[10] = 64'hFFC3_99BD_BD99_C3FF;
	assign fontTable[11] = 64'h0F07_0D7C_CCCC_CC78;
	assign fontTable[12] = 64'h3C66_6666_3C18_7E18;
	assign fontTable[13] = 64'h3F30_3F30_3070_F0E0;
	assign fontTable[14] = 64'h7F63_7F63_6367_E6C0;
	assign fontTable[15] = 64'h995A_3CE7_E73C_5A99;
	assign fontTable[16] = 64'h80E0_F8FE_F8E0_8000;
	assign fontTable[17] = 64'h020E_3EFE_3E0E_0200;
	assign fontTable[18] = 64'h183C_7E18_7E3C_1800;
	assign fontTable[19] = 64'h6666_6666_6600_6600;
	assign fontTable[20] = 64'h7FDB_DB7B_1B1B_1B00;
	assign fontTable[21] = 64'h3E63_3C66_663C_C67C;
	assign fontTable[22] = 64'h0000_0000_7E7E_7E00;
	assign fontTable[23] = 64'h183C_7E18_7E3C_18FF;
	assign fontTable[24] = 64'h183C_7E18_1818_1800;
	assign fontTable[25] = 64'h1818_1818_7E3C_1800;
	assign fontTable[26] = 64'h0018_0CFE_0C18_0000;
	assign fontTable[27] = 64'h0030_60FE_6030_0000;
	assign fontTable[28] = 64'h0000_C0C0_C0FE_0000;
	assign fontTable[29] = 64'h0024_66FF_6624_0000;
	assign fontTable[30] = 64'h0018_3C7E_FFFF_0000;
	assign fontTable[31] = 64'h00FF_FF7E_3C18_0000;
	assign fontTable[32] = 64'h0000_0000_0000_0000;
	assign fontTable[33] = 64'h3078_7830_3000_3000;
	assign fontTable[34] = 64'h6C6C_6C00_0000_0000;
	assign fontTable[35] = 64'h6C6C_FE6C_FE6C_6C00;
	assign fontTable[36] = 64'h307C_C078_0CF8_3000;
	assign fontTable[37] = 64'h00C6_CC18_3066_C600;
	assign fontTable[38] = 64'h386C_3876_DCCC_7600;
	assign fontTable[39] = 64'h6060_C000_0000_0000;
	assign fontTable[40] = 64'h1830_6060_6030_1800;
	assign fontTable[41] = 64'h6030_1818_1830_6000;
	assign fontTable[42] = 64'h0066_3CFF_3C66_0000;
	assign fontTable[43] = 64'h0030_30FC_3030_0000;
	assign fontTable[44] = 64'h0000_0000_0030_3060;
	assign fontTable[45] = 64'h0000_00FC_0000_0000;
	assign fontTable[46] = 64'h0000_0000_0030_3000;
	assign fontTable[47] = 64'h060C_1830_60C0_8000;
	assign fontTable[48] = 64'h7CC6_C6D6_C6C6_7C00;
	assign fontTable[49] = 64'h3070_3030_3030_FC00;
	assign fontTable[50] = 64'h78CC_0C38_60CC_FC00;
	assign fontTable[51] = 64'h78CC_0C38_0CCC_7800;
	assign fontTable[52] = 64'h1C3C_6CCC_FE0C_1E00;
	assign fontTable[53] = 64'hFCC0_F80C_0CCC_7800;
	assign fontTable[54] = 64'h3860_C0F8_CCCC_7800;
	assign fontTable[55] = 64'hFCCC_0C18_3030_3000;
	assign fontTable[56] = 64'h78CC_CC78_CCCC_7800;
	assign fontTable[57] = 64'h78CC_CC7C_0C18_7000;
	assign fontTable[58] = 64'h0030_3000_3030_0000;
	assign fontTable[59] = 64'h0030_3000_3030_6000;
	assign fontTable[60] = 64'h1830_60C0_6030_1800;
	assign fontTable[61] = 64'h0000_FC00_00FC_0000;
	assign fontTable[62] = 64'h6030_180C_1830_6000;
	assign fontTable[63] = 64'h78CC_CC18_3000_3000;
	assign fontTable[64] = 64'h7CC6_DEDE_DEC0_7800;
	assign fontTable[65] = 64'h3078_CCCC_FCCC_CC00;
	assign fontTable[66] = 64'hFC66_667C_6666_FC00;
	assign fontTable[67] = 64'h3C66_C0C0_C066_3C00;
	assign fontTable[68] = 64'hF86C_6666_666C_F800;
	assign fontTable[69] = 64'hFE62_6878_6862_FE00;
	assign fontTable[70] = 64'hFE62_6878_6860_F000;
	assign fontTable[71] = 64'h3C66_C0C0_CE66_3E00;
	assign fontTable[72] = 64'hCCCC_CCFC_CCCC_CC00;
	assign fontTable[73] = 64'h7830_3030_3030_7800;
	assign fontTable[74] = 64'h1E0C_0C0C_CCCC_7800;
	assign fontTable[75] = 64'hC666_6C78_6C66_C600;
	assign fontTable[76] = 64'hF060_6060_6266_FE00;
	assign fontTable[77] = 64'hC6EE_FEFE_D6C6_C600;
	assign fontTable[78] = 64'hC6E6_F6DE_CEC6_C600;
	assign fontTable[79] = 64'h7CC6_C6C6_C6C6_7C00;
	assign fontTable[80] = 64'hFC66_667C_6060_F000;
	assign fontTable[81] = 64'h7CC6_C6C6_C6D6_7C06;
	assign fontTable[82] = 64'hFC66_667C_6C66_E600;
	assign fontTable[83] = 64'h7CC6_6038_0CC6_7C00;
	assign fontTable[84] = 64'hFF99_1818_1818_3C00;
	assign fontTable[85] = 64'hCCCC_CCCC_CCCC_7800;
	assign fontTable[86] = 64'hCCCC_CCCC_CC78_3000;
	assign fontTable[87] = 64'hC6C6_D6FE_FEEE_C600;
	assign fontTable[88] = 64'hC6C6_6C38_6CC6_C600;
	assign fontTable[89] = 64'hCCCC_CC78_3030_7800;
	assign fontTable[90] = 64'hFEC6_8C18_3266_FE00;
	assign fontTable[91] = 64'h7860_6060_6060_7800;
	assign fontTable[92] = 64'hC060_3018_0C06_0200;
	assign fontTable[93] = 64'h7818_1818_1818_7800;
	assign fontTable[94] = 64'h1038_6CC6_0000_0000;
	assign fontTable[95] = 64'h0000_0000_0000_00FF;
	assign fontTable[96] = 64'h3030_1800_0000_0000;
	assign fontTable[97] = 64'h0000_780C_7CCC_7600;
	assign fontTable[98] = 64'hE060_7C66_6666_DC00;
	assign fontTable[99] = 64'h0000_78CC_C0CC_7800;
	assign fontTable[100] = 64'h1C0C_7CCC_CCCC_7600;
	assign fontTable[101] = 64'h0000_78CC_FCC0_7800;
	assign fontTable[102] = 64'h386C_60F0_6060_F000;
	assign fontTable[103] = 64'h0000_76CC_CC7C_0CF8;
	assign fontTable[104] = 64'hE060_6C76_6666_E600;
	assign fontTable[105] = 64'h3000_7030_3030_7800;
	assign fontTable[106] = 64'h0C00_0C0C_0CCC_CC78;
	assign fontTable[107] = 64'hE060_666C_786C_6600;
	assign fontTable[108] = 64'h7030_3030_3030_7800;
	assign fontTable[109] = 64'h0000_CCFE_FED6_D600;
	assign fontTable[110] = 64'h0000_F8CC_CCCC_CC00;
	assign fontTable[111] = 64'h0000_78CC_CCCC_7800;
	assign fontTable[112] = 64'h0000_DC66_667C_60F0;
	assign fontTable[113] = 64'h0000_766C_6C7C_0C1E;
	assign fontTable[114] = 64'h0000_DC76_6060_F000;
	assign fontTable[115] = 64'h0000_7CC0_780C_F800;
	assign fontTable[116] = 64'h1030_7C30_3036_1C00;
	assign fontTable[117] = 64'h0000_CCCC_CCCC_7600;
	assign fontTable[118] = 64'h0000_CCCC_CC78_3000;
	assign fontTable[119] = 64'h0000_C6D6_FEFE_6C00;
	assign fontTable[120] = 64'h0000_C66C_386C_C600;
	assign fontTable[121] = 64'h0000_CCCC_CC7C_0CF8;
	assign fontTable[122] = 64'h0000_FC98_3064_FC00;
	assign fontTable[123] = 64'h1C30_30E0_3030_1C00;
	assign fontTable[124] = 64'h1818_1800_1818_1800;
	assign fontTable[125] = 64'hE030_301C_3030_E000;
	assign fontTable[126] = 64'h0000_72D6_9C00_0000;
	assign fontTable[127] = 64'h0010_386C_C6C6_FE00;

	always @(ascii)begin
		case(line)
		8'd0: out <= fontTable[ascii][63:56];
		8'd1: out <= fontTable[ascii][55:48];
		8'd2: out <= fontTable[ascii][47:40];
		8'd3: out <= fontTable[ascii][39:32];
		8'd4: out <= fontTable[ascii][31:24];
		8'd5: out <= fontTable[ascii][23:16];
		8'd6: out <= fontTable[ascii][15:8];
		8'd7: out <= fontTable[ascii][7:0];
		endcase
	end
	
endmodule
