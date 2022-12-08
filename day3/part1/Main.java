import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

class Main {
	public static void main(String[] args) {
		int sum = 0;

		try {
			File myObj = new File("input.txt");
			Scanner myReader = new Scanner(myObj);
			while (myReader.hasNextLine()) {
				String data = myReader.nextLine();
				int length = data.length();

				Set<Character> firstHalfSet = new HashSet<Character>();
				Set<Character> secondHalfSet = new HashSet<Character>();

				// Populate sets with first and second half of string
				for (int i = 0; i < data.length(); i++) {
					char c = data.charAt(i);
					if (i < length / 2) {
						firstHalfSet.add(c);
					} else {
						secondHalfSet.add(c);
					}
				}

				// Check if sets contain the same characters
				for (char c : firstHalfSet) {
					if (secondHalfSet.contains(c)) {
						sum += getValue(c);
						break;
					}
				}
			}

			System.out.println(sum);

			myReader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	private static int getValue(char c) {
		return Character.getNumericValue(c) + (Character.isUpperCase(c) ? 17 : -9);
	}
}
