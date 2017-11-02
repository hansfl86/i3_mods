#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) \
	({ __typeof__ (a) _a = (a); \
	 __typeof__ (b) _b = (b); \
	_a > _b ? _a : _b; })

#define min(a,b) \
	({ __typeof__ (a) _a = (a); \
	 __typeof__ (b) _b = (b); \
	_a < _b ? _a : _b; })

int getMaxValue()
{
	FILE *max_file;
	char buff[4];
	int max;

       	max_file = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");
	fgets(buff, 4, (FILE*)max_file);
	fclose(max_file);
	max = atoi(buff);
	return max;
}

int getCurrentValue()
{
	FILE *current_file;
	char buff[4];
	int current;

       	current_file = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
	fgets(buff, 4, (FILE*)current_file);
	fclose(current_file);
	current = atoi(buff);
	return current;
}



void setNewValue(int *new)
{
	FILE *fp;
	fp = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
	fprintf(fp, "%d", *new);
}

int main(int argc, char *argv[])
{
	//fprintf(fp, "Hello");
	int max = getMaxValue();
	int cur = getCurrentValue();
	int new = cur;
	int delta;

	char *val = argv[1];

	if (strcmp(val, "inc") == 0)
	{
		delta = 100;
	}
	else if (strcmp(val, "dec") == 0)
	{
		delta = -100;
	}
	else
	{
		return 1;
	}

	// TODO: Make the brighness follow a invertible function instead.
	if (cur > 900)
	{
		cur = 1000;
	}

	else if (cur < 300 && cur > 150)
	{
		delta /= 2;
	}
	else if (cur <= 150)
	{
		delta /= 4;
	}
	new = cur + delta;
	
	new = min(new, max);
	new = max(new, 0);

	setNewValue(&new);
	return 0;
}
