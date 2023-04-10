# easter-day

Simple C implementation of the Carter's and CalendarBede deduction algorithm's for the calculation of the easter day for a given year in the gregorian calendar.  

# usage

Include the header [easter.h](./easter.h) in you source file and that's it. Example:

[`main.c`](./main.c):
```c
int main(int argq, char **argv){
	if(argq < 2){
		printf("Please pass the year as the first argument\n");
		return 1;
	}

	regex_t reg;
	regcomp(&reg, "^\\d{4}$", 0);

	if(
		argv[1] == NULL ||
		(argv[1] != NULL && !regexec(&reg, argv[1], 0, NULL, 0))
	){
		printf("Passed year is null or invalid: '%s'\n", argv[1]);
		return 1;
	}

	int year = atoi(argv[1]);

	errno = 0;
	struct tm res1 = easterDate(year);
	if(!errno){
		char str1[50];
		strftime(str1, 50, "%D - %Y %B %d %A", &res1);
		printf("Easter all gregorian: '%s'\n", str1);
	}
	else{
		printf("Error easter all gregorian: %s\n", strerror(errno));
	}

	errno = 0;
	struct tm res2 = easterDate19002099(year);
	if(!errno){
		char str2[50];	
		strftime(str2, 50, "%D - %Y %B %d %A", &res2);
		printf("Easter 1900-2099:     '%s'\n", str2);
	}
	else{
		printf("Error easter 1900-2099: %s\n", strerror(errno));
	}

	return 0;
}
```

# sources

* [CalendarBede](https://www.calendarbede.com/book/carter-easter-algorithm)