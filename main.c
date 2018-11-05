/*
Portc[4:0] = 1, Anode
PortD[7:3] = 0, Catode
Therfore we need to set some of them to zero
*/
#include <avr/io.h>
#include <avr/interrupt.h>
//portc's
uint8_t PCs[5] = {PORTC0,PORTC1,PORTC2,PORTC3,PORTC4};
//make bitmap

struct bitmap
{
	uint8_t map[5];
};
typedef struct bitmap Bitmap;

const Bitmap space = {{
	0b0,
	0b0,
	0b0,
	0b0,
	0b0}};

const Bitmap smiley = {{
	0b10001,
	0b10001,
	0b00000,
	0b10001,
	0b01110
	}};

const Bitmap A = {{
	0b00100,
	0b01010,
	0b01010,
	0b01110,
0b01010}};

const Bitmap B = {{
	0b01110,
	0b01010,
	0b00110,
	0b01010,
0b01110}};

const Bitmap C = {{
	0b01110,
	0b00010,
	0b00010,
	0b00010,
	0b01110}};

const Bitmap D = {{
	0b00110,
	0b01010,
	0b01010,
	0b01010,
	0b00110}};

const Bitmap E = {{
	0b01110,
	0b00010,
	0b00110,
	0b00010,
	0b01110}};

const Bitmap F = {{
	0b01110,
	0b00010,
	0b00110,
	0b00010,
	0b00010}};

const Bitmap G = {{
	0b01110,
	0b00010,
	0b01010,
	0b01010,
0b01110}};

const Bitmap H = {{
	0b01010,
	0b01010,
	0b01110,
	0b01010,
0b01010}};

const Bitmap I = {{
	0b01110,
	0b00100,
	0b00100,
	0b00100,
0b01110}};

const Bitmap J = {{
	0b01000,
	0b01000,
	0b01000,
	0b01010,
	0b01110}};

const Bitmap K = {{
	0b01010,
	0b01010,
	0b00110,
	0b01010,
0b01010}};

const Bitmap L = {{
	0b00010,
	0b00010,
	0b00010,
	0b00010,
	0b01110}};

const Bitmap M = {{
	0b01010,
	0b01110,
	0b01110,
	0b01010,
0b01010}};

const Bitmap N = {{
	0b00010,
	0b01110,
	0b01010,
	0b01010,
	0b01010}};

const Bitmap O = {{
	0b01110,
	0b01010,
	0b01010,
	0b01010,
0b01110}};

const Bitmap P = {{
	0b01110,
	0b01010,
	0b01110,
	0b00010,
	0b00010}};

const Bitmap Q = {{
	0b01110,
	0b01010,
	0b01010,
	0b01010,
0b01111}};

const Bitmap R = {{
	0b01110,
	0b01010,
	0b00110,
	0b01010,
	0b01010}};

const Bitmap S = {{
	0b01110,
	0b00010,
	0b01110,
	0b01000,
	0b01110}};

const Bitmap T = {{
	0b01110,
	0b00100,
	0b00100,
	0b00100,
0b00100}};

const Bitmap U = {{
	0b01010,
	0b01010,
	0b01010,
	0b01010,
0b01110}};

const Bitmap V = {{
	0b01010,
	0b01010,
	0b01010,
	0b01010,
0b00100}};

const Bitmap W = {{
	0b10001,
	0b10001,
	0b10001,
	0b00100,
	0b01010}};

const Bitmap X = {{
	0b01010,
	0b01010,
	0b00100,
	0b01010,
0b01010}};

const Bitmap Y = {{
	0b01010,
	0b01010,
	0b00100,
	0b00100,
0b00100}};

const Bitmap Z = {{
	0b01110,
	0b01000,
	0b00100,
	0b00010,
	0b01110}};

const Bitmap* string[] = {&space, &H, &E, &J, &space, &L, &O, &G, &O, &S, &space, &T, &A, &K, &space, &F, &O, &R, &space, &G, &O, &D, &space, &P,&R, &A, &K, &T, &I, &K, &space, &smiley, &space};
volatile Bitmap fb;
uint32_t offset;
void init_clock();
void renderText(Bitmap* string[], uint32_t offset, Bitmap* fb, uint8_t length);
uint8_t leftix(uint32_t offset, uint8_t length);
uint8_t rightix(uint32_t offset, uint8_t length);
Bitmap* leftChar(const Bitmap* _char, Bitmap* out, uint8_t shift);
Bitmap* rightChar(const Bitmap* c, Bitmap* out, uint8_t shift);
void overlay(const Bitmap* b1, const Bitmap* b2, Bitmap* fb);
void fbreset(Bitmap* fb);
uint8_t bitmapEqual(Bitmap* a, Bitmap* b);

void showBitmap(Bitmap b, int t);
void test(Bitmap name, int test);

int main(void){
	//Make PORTC and PORTD data direction write
	DDRC |= 0b00011111;
	DDRD |= 0b11111000;
	uint32_t offset = 0; 
	//	init_clock();
	//while (1)
	/*{
        test(L, leftix(24, 10) == 4);
        test(O, leftix(50, 10) == 0);
        test(E, leftix(0, 10)  == 0);
		test(L, rightix(24, 10) == 5);
        test(O, rightix(49, 10) == 0);
        test(E, rightix(0, 10)  == 1);
		Bitmap outl, outr;
		leftChar(&O,&outr,1);
		test(O, bitmapEqual(&outl, &O1));	
		rightChar(&O,&outl,4);
		test(O, bitmapEqual(&outr, &O2));
		Bitmap overlayed;
		overlay(&O1, &O2, &overlayed);
		test(O, bitmapEqual(&overlayed, &overlayExpectation));
		
		}*/
	
	long int t = 0;
	while(1){
		if (offset < t / 3500)
		{
		  renderText(string, offset, &fb, (sizeof(string)/sizeof(Bitmap*)));
		  offset = t / 3500;
		}
		light(&fb);
		t++;
	}
}

/*
void init_clock(){
	//Put timer0  out of power saving mode
	PRR |= (1<<PRTIM0);

	//Setting prescaler to 64 and clock to clkI/O
	TCCR0B &= ~(3);
	TCCR2B |= 0X2;
	//Initialize TCNT2
	TCNT2 = 0;
	PRR &= (1<<PRTIM0);
	//Set clock to system clock, CS0[2:0]=0x;
	TCCR1B &= ~(9<<CS00);
	TCCR0B |= 0b011;
	//Initialize clock counter
	TCNT0 = 0;
}*/

uint8_t bitmapEqual(Bitmap* a, Bitmap* b)
{
	for(uint8_t row = 0; row < 5; row++)
	{
		if(a->map[row]!=b->map[row])
		{
			return 0;
		}
	}
	return 1;	
}

void test(Bitmap name, int test)
{
	showBitmap(name, 1);
	if (test)
	{
		showBitmap(R,1);
	}
	else
	{
		showBitmap(W,1);
	}
}

void showBitmap(Bitmap b, int t){
	uint32_t t2 = ((uint32_t) t)* 100000;
	while (t2>0)
	{
		light(&b);
		t2--;
	}
}

/*void  shift(Bitmap* in1, Bitmap* in2, Bitmap* out, uint8_t left_shift ){
	for(int row = 4; row >= 0; --row){
		out->map[row] = ((in1->map[row] << left_shift) | (in2->map[row] >> (5 - left_shift)));
		
	}
	return out;
}*/


void renderText(Bitmap* string[], uint32_t offset, Bitmap* fb, uint8_t length){
	Bitmap outl, outr;
	fbreset(fb);
	overlay(leftChar( string[(leftix(offset, length))], &outl, (offset%5) ), rightChar(string[rightix(offset, length)], &outr, (offset%5)), fb); 
}

uint8_t leftix(uint32_t offset, uint8_t length){
	return (offset/5) % length;
}

uint8_t rightix(uint32_t offset, uint8_t length){
	return (leftix(offset, length)+1) % length;
}

Bitmap* leftChar(const Bitmap* _char, Bitmap* out, uint8_t shift){
	for(int row = 4; row >= 0; row--){
		out->map[row]=(_char->map[row]>>shift);
	}
	return out;
}

Bitmap* rightChar(const Bitmap* c, Bitmap* out, uint8_t shift){
	for(int row = 4; row >= 0; row--){
		out->map[row] = ( c->map[row] << (5-shift));
	}
	return out;
}

void overlay(const Bitmap* b1, const Bitmap* b2, Bitmap* fb){
	for(int row = 4; row >= 0; row--){
		fb->map[row] = (b1->map[row]|b2->map[row]);
	}
}

void fbreset(Bitmap* fb){
	for(int row = 4; row >= 0; --row){
		fb->map[row] = 0;
	}
}

void light(Bitmap* b){
	//This for loop will iterate through the map
	//PORTD = 255;
	uint8_t PORTDB, PORTCB;
	for (int row = 4; row >= 0; --row){ 
			PORTDB = (~(b->map[row])<<PORTD3);
			PORTCB = (1<<PCs[row]);
			PORTC = PORTCB;
			PORTD = PORTDB;
	}
} 
