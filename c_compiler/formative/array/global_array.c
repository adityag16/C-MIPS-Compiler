
int array[35];

int ffff(){
	int x;
	int i;

	for (i = 0; i < 35; i++)
	{
		array[i] = i;
	}

	for (i = 0; i < 35; i++)
	{
		x+=array[i];
	}

	return x;

}
