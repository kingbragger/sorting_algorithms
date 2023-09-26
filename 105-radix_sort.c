#include"sort.h"

int get_max(int *array, int size);
void radix_sort(int *array, size_t size);
void radix_counting_sort(int *array, size_t size, int sig, int *buff);

/**
 * get_max - Get the maximum value in an array of integers.
 * @array: An array of integers.
 * @size: The size of the array.
 *
 * Return: The maximum integer in the array.
 */

int get_max(int *array, int size)
{
	int max, i;

	for (max = array[0], i = 1; i < size; i++)
	{
		if (array[i] > max)
			max = array[i];
	}

	return (max);
}

/**
 * radix_counting_sort - t Sorts the significant's digits of an array of int's
 *                       in ascending order using the counting sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 * @sig: The significant digit to sort on.
 * @buff: A buffer to store the sorted array.
 */
void radix_counting_sort(int *array, size_t size, int sig, int *buff)
{
	int count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	size_t z;

	for (z = 0; z < size; z++)
		count[(array[z] / sig) % 10] += 1;

	for (z = 0; z < 10; z++)
		count[z] += count[z - 1];

	for (z = size - 1; (int)z >= 0; z--)
	{
		buff[count[(array[z] / sig) % 10] - 1] = array[z];
		count[(array[z] / sig) % 10] -= 1;
	}

	for (z = 0; z < size; z++)
		array[z] = buff[z];
}

/**
 * radix_sort - Sorts an arrays of int's in ascending
 *            order using the radix sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 *
 * Description: Implements the LSD radix sort algorithm. Prints
 * the array after each significant digit increase.
 */

void radix_sort(int *array, size_t size)
{
	int sig, max, *buff;

	if (array == NULL || size < 2)
		return;

	buff = malloc(sizeof(int) * size);
	if (buff == NULL)
		return;

	max = get_max(array, size);
	for (sig = 1; sig / max > 0; sig *= 10)
	{
		radix_counting_sort(array, size, sig, buff);
		print_array(array, size);
	}

	free(buff);
}
