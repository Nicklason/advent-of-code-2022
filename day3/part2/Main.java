import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

class Main {
	public static void main(String[] args) {
		int sum = 0;

		try {
			File myObj = new File("input.txt");
			Scanner myReader = new Scanner(myObj);

			ArrayList<Set<Character>> sets = new ArrayList<>();
			while (myReader.hasNextLine()) {
				String data = myReader.nextLine();

				Set<Character> set = new HashSet<>();
				sets.add(set);

				// Populate sets with characters
				for (int i = 0; i < data.length(); i++) {
					char c = data.charAt(i);
					set.add(c);
				}

				if (sets.size() == 3) {
					// Check if sets contain the same characters
					for (char c : sets.get(0)) {
						if (sets.get(1).contains(c) && sets.get(2).contains(c)) {
							sum += getValue(c);
							break;
						}
					}

					sets.clear();
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
