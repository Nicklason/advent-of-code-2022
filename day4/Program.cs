namespace day4
{
    class Program
    {
        static void Main(string[] args)
        {
            // Read file called input.txt
            string[] lines = System.IO.File.ReadAllLines(@"input.txt");

            int contain = 0;
            int overlap = 0;

            // Loop each line
            foreach (string line in lines)
            {
                // Split line into words
                string[] pairs = line.Split(',');

                // Get start and end of each pair
                int firstStart = int.Parse(pairs[0].Split('-')[0]);
                int firstEnd = int.Parse(pairs[0].Split('-')[1]);

                int secondStart = int.Parse(pairs[1].Split('-')[0]);
                int secondEnd = int.Parse(pairs[1].Split('-')[1]);


                // Check if first pair is within second pair
                if (firstStart >= secondStart && firstEnd <= secondEnd)
                {
                    contain++;
                }
                else if (secondStart >= firstStart && secondEnd <= firstEnd)
                {
                    contain++;
                }

                // Check if first pair overlaps second pair
                if (firstStart <= secondStart && firstEnd >= secondStart)
                {
                    overlap++;
                }
                else if (secondStart <= firstStart && secondEnd >= firstStart)
                {
                    overlap++;
                }
            }

            System.Console.WriteLine("Part 1: " + contain);
            System.Console.WriteLine("Part 2: " + overlap);
        }
    }
}
