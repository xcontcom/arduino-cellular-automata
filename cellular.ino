#include <MD_MAX72xx.h >
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 1
#define CLK_PIN 13
// or SCK
#define DATA_PIN 11
#define CS_PIN 10
// or MOSI
// or SS
#define DELAYTIME 100  // in milliseconds
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int xx=8;
const int yy=8;
bool a[xx][yy];
bool temp[xx][yy];
bool r[18]={0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0};
bool rule[512];
int q;

void setup() {
		mx.begin();
		mx.clear();
		mx.control(MD_MAX72XX::INTENSITY, 1);
		randomSeed(analogRead(0));
		for(int x=0;x<xx;x++){
			for(int y=0;y<yy;y++){
				a[x][y]=0;
				//random(0,2); //use random instead
			}
		}
		
		a[3][3]=1;
		a[3][4]=1;
		a[3][5]=1;
		a[4][3]=1;
		a[5][4]=1;
		
		//use random instead of glider
		/*
		for(int i=0;i<18;i++){
			r[i]=random(0,2);
		}
		*/
		
		for(int i=0;i<512;i++){
			q=((i>>4)&1)*8;
			for(int j=0;j<9;j++){
				q+=(i>>j)&1;
			}
			rule[i]=r[q];
		}
}
void loop() {
		delay(DELAYTIME);
		mx.clear();
		int xm, xp, ym, yp;
		for(int x=0;x<xx;x++){
			xm=x-1;
			if(xm==-1) xm=xx-1;
			xp=x+1;
			if(xp==xx) xp=0;
			for(int y=0;y<yy;y++){
				ym=y-1;
				if(ym==-1) ym=yy-1;
				yp=y+1;
				if(yp==yy) yp=0;
				q=a[xm][ym];
				q=(q<<1)+a[x][ym];
				q=(q<<1)+a[xp][ym];
				q=(q<<1)+a[xm][y];
				q=(q<<1)+a[x][y];
				q=(q<<1)+a[xp][y];
				q=(q<<1)+a[xm][yp];
				q=(q<<1)+a[x][yp];
				q=(q<<1)+a[xp][yp];
				temp[x][y]=rule[q];
				if(temp[x][y]) mx.setPoint(x,y,true);
			}
		}
		for(int x=0;x<xx;x++){
			for(int y=0;y<yy;y++){
				a[x][y]=temp[x][y];
			}
		}
}