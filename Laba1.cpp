#include <stdio.h>
#include <math.h>
const double pi = 3.14159265;
#define min 1e-8
double c_fabs(double x) {
	return (x < 0 ? -x : x); /*модуль числа*/
}
double ct_fmod(double x) {
	while (c_fabs(x) > (2 * pi)) x -= (2 * pi); /* функция для того, чтобы число
	было <2pi*/
	return x;
}
double rnd(double chislo, long znaki) /*округление с заданной
точностью*/
{
	double result = round(chislo * pow(10, znaki) / pow(10, znaki));
	return result;
}
double tg_taylor(double x, int accuracy) { /*под точностью понимается
количество итераций ряда Тейлора*/
	double sin_x = x;
	double cos_x = x;
	int n = 0;
	double s, a, k;
	s = a = ct_fmod(x);
	k = ct_fmod(x);
	while (n<accuracy && c_fabs(x)>min) { //находим sin(x)
		n++;
		a *= (-1) * (k * k) / (2 * n * (2 * n + 1));
		s += a;
	}
	sin_x = s;
	n = 0; /*обнуляем счетчик*/
	s = a = 1;
	k = ct_fmod(x);
	while (n<accuracy && c_fabs(x)>min) { /*находим cos(x)*/
		n++;
		a *= (-1) * (k * k) / (2 * n * (2 * n - 1));
		s += a;
	}
	cos_x = s;
	x = sin_x / cos_x; /*tg x*/
	return x;
}
void test(int n) {
	double t = 0, s = 0;
	int acc = 0, l = 0, k = 0, h = 0, d = 0;
	printf("Please write value x and accuracy of Taylor Series:\n");
	while (h < n) {
		scanf("%lf%i", &t, &acc);
		if (c_fabs(t) != pi / 2) {
			s = tg_taylor(t, acc);
			printf("tangent x: %f, built-in: %f\n accuracy:%i iterations\n",s, tan(t), acc);
				if (rnd(s, 3) == rnd(tan(t), 3)) k++;
				else l++;
		}
		else {
			printf("Definition Error\n");
			d++;
		}
		h++;
	}
	if ((k) == (n - d) && n != d) printf("0\n");
	else if ((k) != (n - d)) printf("There are %i mistakes", l);
	else printf("You wrote wrong value");
}
void rd_task() {
	double t = 0, s = 0;
	int acc = 1000, l = 0, k = 0, h = 0, d = 0;
	int n = 10;
	double rt[10];
	rt[0] = 2;
	rt[1] = -pi / 2;
	rt[2] = 3.14;
	rt[3] = 6;
	rt[4] = 0.156;
	rt[5] = 200;
	rt[6] = 356;
	rt[7] = 900.156;
	rt[8] = 58.6;
	rt[9] = pi / 2;
	while (h < n) {
		t = rt[h];
		if (c_fabs(t) != pi / 2) {
			s = tg_taylor(t, acc);
			printf("tangent x: %f, built-in: %f\n accuracy:%i iterations\n",s, tan(t), acc);
				if (rnd(s, 3) == rnd(tan(t), 3)) k++;
				else l++;
		}
		else {
			printf("Definition Error\n");
			d++;
		}
		h++;
	}
	if ((k) == (n - d)) printf("0\n");
	else printf("There are %i mistakes", l);
}
int main(void) {
	int n = 0;
	int k = 1, f;
	printf("Welcome, do you want to test program with given numbers or try to write yourself ? \n");
		printf("Please type '1' to write yourself or something else to read test\n");
			scanf("%d", &f);
	if (k == f) {
		printf("Please write how many test tasks you wanna write:\n");
		scanf("%i", &n);
		test(n);
	}
	else {
		rd_task();
	}
	return 0;
}