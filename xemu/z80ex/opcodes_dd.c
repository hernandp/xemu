/* autogenerated from ./opcodes_ddfd.dat, do not edit */

/*ADD IX,BC*/
static void op_DD_0x09(void)
{
	ADD16(IX,BC);
	T_WAIT_UNTIL(11);
	return;
}

/*ADD IX,DE*/
static void op_DD_0x19(void)
{
	ADD16(IX,DE);
	T_WAIT_UNTIL(11);
	return;
}

/*LD IX,@*/
static void op_DD_0x21(void)
{
	temp_word.b.l=READ_OP();
	temp_word.b.h=READ_OP();
	LD16(IX,temp_word.w);
	T_WAIT_UNTIL(10);
	return;
}

/*LD (@),IX*/
static void op_DD_0x22(void)
{
	temp_addr.b.l=READ_OP();
	temp_addr.b.h=READ_OP();
	LD_RP_TO_ADDR_MPTR_16(temp_word.w,IX, temp_addr.w);
	WRITE_MEM(temp_addr.w,temp_word.b.l,10);
	WRITE_MEM(temp_addr.w+1,temp_word.b.h,13);
	T_WAIT_UNTIL(16);
	return;
}

/*INC IX*/
static void op_DD_0x23(void)
{
	INC16(IX);
	T_WAIT_UNTIL(6);
	return;
}

/*INC IXH*/
static void op_DD_0x24(void)
{
	INC(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*DEC IXH*/
static void op_DD_0x25(void)
{
	DEC(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXH,#*/
static void op_DD_0x26(void)
{
	temp_byte=READ_OP();
	LD(IXH,temp_byte);
	T_WAIT_UNTIL(7);
	return;
}

/*ADD IX,IX*/
static void op_DD_0x29(void)
{
	ADD16(IX,IX);
	T_WAIT_UNTIL(11);
	return;
}

/*LD IX,(@)*/
static void op_DD_0x2a(void)
{
	temp_addr.b.l=READ_OP();
	temp_addr.b.h=READ_OP();
	READ_MEM(temp_word.b.l,temp_addr.w,10);
	READ_MEM(temp_word.b.h,temp_addr.w+1,13);
	LD_RP_FROM_ADDR_MPTR_16(IX,temp_word.w, temp_addr.w);
	T_WAIT_UNTIL(16);
	return;
}

/*DEC IX*/
static void op_DD_0x2b(void)
{
	DEC16(IX);
	T_WAIT_UNTIL(6);
	return;
}

/*INC IXL*/
static void op_DD_0x2c(void)
{
	INC(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*DEC IXL*/
static void op_DD_0x2d(void)
{
	DEC(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,#*/
static void op_DD_0x2e(void)
{
	temp_byte=READ_OP();
	LD(IXL,temp_byte);
	T_WAIT_UNTIL(7);
	return;
}

/*INC (IX+$)*/
static void op_DD_0x34(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	INC(temp_byte);
	WRITE_MEM((IX+temp_byte_s),temp_byte,16);
	T_WAIT_UNTIL(19);
	return;
}

/*DEC (IX+$)*/
static void op_DD_0x35(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	DEC(temp_byte);
	WRITE_MEM((IX+temp_byte_s),temp_byte,16);
	T_WAIT_UNTIL(19);
	return;
}

/*LD (IX+$),#*/
static void op_DD_0x36(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	temp_byte=READ_OP();
	LD(temp_byte,temp_byte);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*ADD IX,SP*/
static void op_DD_0x39(void)
{
	ADD16(IX,SP);
	T_WAIT_UNTIL(11);
	return;
}

/*LD B,IXH*/
static void op_DD_0x44(void)
{
	LD(B,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD B,IXL*/
static void op_DD_0x45(void)
{
	LD(B,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD B,(IX+$)*/
static void op_DD_0x46(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(B,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*LD C,IXH*/
static void op_DD_0x4c(void)
{
	LD(C,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD C,IXL*/
static void op_DD_0x4d(void)
{
	LD(C,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD C,(IX+$)*/
static void op_DD_0x4e(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(C,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*LD D,IXH*/
static void op_DD_0x54(void)
{
	LD(D,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD D,IXL*/
static void op_DD_0x55(void)
{
	LD(D,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD D,(IX+$)*/
static void op_DD_0x56(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(D,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*LD E,IXH*/
static void op_DD_0x5c(void)
{
	LD(E,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD E,IXL*/
static void op_DD_0x5d(void)
{
	LD(E,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD E,(IX+$)*/
static void op_DD_0x5e(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(E,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*LD IXH,B*/
static void op_DD_0x60(void)
{
	LD(IXH,B);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXH,C*/
static void op_DD_0x61(void)
{
	LD(IXH,C);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXH,D*/
static void op_DD_0x62(void)
{
	LD(IXH,D);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXH,E*/
static void op_DD_0x63(void)
{
	LD(IXH,E);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXH,IXH*/
static void op_DD_0x64(void)
{
	LD(IXH,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXH,IXL*/
static void op_DD_0x65(void)
{
	LD(IXH,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD H,(IX+$)*/
static void op_DD_0x66(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(H,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*LD IXH,A*/
static void op_DD_0x67(void)
{
	LD(IXH,A);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,B*/
static void op_DD_0x68(void)
{
	LD(IXL,B);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,C*/
static void op_DD_0x69(void)
{
	LD(IXL,C);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,D*/
static void op_DD_0x6a(void)
{
	LD(IXL,D);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,E*/
static void op_DD_0x6b(void)
{
	LD(IXL,E);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,IXH*/
static void op_DD_0x6c(void)
{
	LD(IXL,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD IXL,IXL*/
static void op_DD_0x6d(void)
{
	LD(IXL,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD L,(IX+$)*/
static void op_DD_0x6e(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(L,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*LD IXL,A*/
static void op_DD_0x6f(void)
{
	LD(IXL,A);
	T_WAIT_UNTIL(4);
	return;
}

/*LD (IX+$),B*/
static void op_DD_0x70(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,B);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD (IX+$),C*/
static void op_DD_0x71(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,C);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD (IX+$),D*/
static void op_DD_0x72(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,D);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD (IX+$),E*/
static void op_DD_0x73(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,E);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD (IX+$),H*/
static void op_DD_0x74(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,H);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD (IX+$),L*/
static void op_DD_0x75(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,L);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD (IX+$),A*/
static void op_DD_0x77(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	LD(temp_byte,A);
	WRITE_MEM((IX+temp_byte_s),temp_byte,12);
	T_WAIT_UNTIL(15);
	return;
}

/*LD A,IXH*/
static void op_DD_0x7c(void)
{
	LD(A,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*LD A,IXL*/
static void op_DD_0x7d(void)
{
	LD(A,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*LD A,(IX+$)*/
static void op_DD_0x7e(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	LD(A,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*ADD A,IXH*/
static void op_DD_0x84(void)
{
	ADD(A,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*ADD A,IXL*/
static void op_DD_0x85(void)
{
	ADD(A,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*ADD A,(IX+$)*/
static void op_DD_0x86(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	ADD(A,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*ADC A,IXH*/
static void op_DD_0x8c(void)
{
	ADC(A,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*ADC A,IXL*/
static void op_DD_0x8d(void)
{
	ADC(A,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*ADC A,(IX+$)*/
static void op_DD_0x8e(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	ADC(A,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*SUB IXH*/
static void op_DD_0x94(void)
{
	SUB(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*SUB IXL*/
static void op_DD_0x95(void)
{
	SUB(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*SUB (IX+$)*/
static void op_DD_0x96(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	SUB(temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*SBC A,IXH*/
static void op_DD_0x9c(void)
{
	SBC(A,IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*SBC A,IXL*/
static void op_DD_0x9d(void)
{
	SBC(A,IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*SBC A,(IX+$)*/
static void op_DD_0x9e(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	SBC(A,temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*AND IXH*/
static void op_DD_0xa4(void)
{
	AND(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*AND IXL*/
static void op_DD_0xa5(void)
{
	AND(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*AND (IX+$)*/
static void op_DD_0xa6(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	AND(temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*XOR IXH*/
static void op_DD_0xac(void)
{
	XOR(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*XOR IXL*/
static void op_DD_0xad(void)
{
	XOR(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*XOR (IX+$)*/
static void op_DD_0xae(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	XOR(temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*OR IXH*/
static void op_DD_0xb4(void)
{
	OR(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*OR IXL*/
static void op_DD_0xb5(void)
{
	OR(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*OR (IX+$)*/
static void op_DD_0xb6(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	OR(temp_byte);
	T_WAIT_UNTIL(15);
	return;
}

/*CP IXH*/
static void op_DD_0xbc(void)
{
	CP(IXH);
	T_WAIT_UNTIL(4);
	return;
}

/*CP IXL*/
static void op_DD_0xbd(void)
{
	CP(IXL);
	T_WAIT_UNTIL(4);
	return;
}

/*CP (IX+$)*/
static void op_DD_0xbe(void)
{
	temp_byte=READ_OP();
	temp_byte_s=(temp_byte & 0x80)? -(((~temp_byte) & 0x7f)+1): temp_byte;
	MEMPTR=(IX+temp_byte_s);
	READ_MEM(temp_byte,(IX+temp_byte_s),12);
	CP(temp_byte);
	T_WAIT_UNTIL(15);
	return;
}


/*POP IX*/
static void op_DD_0xe1(void)
{
	POP(IX, /*rd*/4,7);
	T_WAIT_UNTIL(10);
	return;
}

/*EX (SP),IX*/
static void op_DD_0xe3(void)
{
	READ_MEM(temp_word.b.l,(SP),4);
	READ_MEM(temp_word.b.h,(SP+1),7);
	EX_MPTR(temp_word.w,IX);
	WRITE_MEM((SP),temp_word.b.l,11);
	WRITE_MEM((SP+1),temp_word.b.h,14);
	T_WAIT_UNTIL(19);
	return;
}

/*PUSH IX*/
static void op_DD_0xe5(void)
{
	PUSH(IX, /*wr*/5,8);
	T_WAIT_UNTIL(11);
	return;
}

/*JP IX*/
static void op_DD_0xe9(void)
{
	JP_NO_MPTR(IX);
	T_WAIT_UNTIL(4);
	return;
}

/*LD SP,IX*/
static void op_DD_0xf9(void)
{
	LD16(SP,IX);
	T_WAIT_UNTIL(6);
	return;
}



/**/
static const z80ex_opcode_fn opcodes_dd[0x100] = {
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , op_DD_0x09    , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , op_DD_0x19    , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , op_DD_0x21    , op_DD_0x22    , op_DD_0x23    ,
 op_DD_0x24    , op_DD_0x25    , op_DD_0x26    , NULL          ,
 NULL          , op_DD_0x29    , op_DD_0x2a    , op_DD_0x2b    ,
 op_DD_0x2c    , op_DD_0x2d    , op_DD_0x2e    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x34    , op_DD_0x35    , op_DD_0x36    , NULL          ,
 NULL          , op_DD_0x39    , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x44    , op_DD_0x45    , op_DD_0x46    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x4c    , op_DD_0x4d    , op_DD_0x4e    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x54    , op_DD_0x55    , op_DD_0x56    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x5c    , op_DD_0x5d    , op_DD_0x5e    , NULL          ,
 op_DD_0x60    , op_DD_0x61    , op_DD_0x62    , op_DD_0x63    ,
 op_DD_0x64    , op_DD_0x65    , op_DD_0x66    , op_DD_0x67    ,
 op_DD_0x68    , op_DD_0x69    , op_DD_0x6a    , op_DD_0x6b    ,
 op_DD_0x6c    , op_DD_0x6d    , op_DD_0x6e    , op_DD_0x6f    ,
 op_DD_0x70    , op_DD_0x71    , op_DD_0x72    , op_DD_0x73    ,
 op_DD_0x74    , op_DD_0x75    , NULL          , op_DD_0x77    ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x7c    , op_DD_0x7d    , op_DD_0x7e    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x84    , op_DD_0x85    , op_DD_0x86    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x8c    , op_DD_0x8d    , op_DD_0x8e    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x94    , op_DD_0x95    , op_DD_0x96    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0x9c    , op_DD_0x9d    , op_DD_0x9e    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0xa4    , op_DD_0xa5    , op_DD_0xa6    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0xac    , op_DD_0xad    , op_DD_0xae    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0xb4    , op_DD_0xb5    , op_DD_0xb6    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 op_DD_0xbc    , op_DD_0xbd    , op_DD_0xbe    , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , op_DD_0xe1    , NULL          , op_DD_0xe3    ,
 NULL          , op_DD_0xe5    , NULL          , NULL          ,
 NULL          , op_DD_0xe9    , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          ,
 NULL          , op_DD_0xf9    , NULL          , NULL          ,
 NULL          , NULL          , NULL          , NULL          
};
