//ArrayUtils.c
class ArrayUtils
{
    static void ShuffleArray(array<string> arr)
    {
        for (int i = arr.Count() - 1; i > 0; i--)
        {
            int j = Math.RandomInt(0, i + 1);
            string temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

