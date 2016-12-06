/**
 * @author Ray
 * @since 2016-04-05
 * Use function to split the logic, make code easier to read and maintain.
 * Reference: Clean Code Chapter
 */
public class GuessStatisticsMessage {

    /**
    *  The straightforward way to write a function, determine the output based on the count number.
    **/
    private void printGuessStatistics(char candidate, int count) {
        String number;
        String verb;
        String pluralModifier;
        if (count == 0) {
            number = "no";
            verb = "are";
            pluralModifier = "s";
        } else if (count == 1) {
            number = "1";
            verb = "is";
            pluralModifier = "";
        } else {
            number = Integer.toString(count);
            verb = "are";
            pluralModifier = "s";
        }
        String guessMessage = String.format(
                "There %s %s %s%s", verb, number, candidate, pluralModifier );
        System.out.println(guessMessage);
    }

    /**
     * First, use a class to wrap the three variables.
     * Second, use different functions to show situations, named by meaningful words to show the intention.
     **/
    private String number;
    private String verb;
    private String pluralModifier;

    public String make(char candidate, int count){
        createPluralDependentMessageParts(count);
        return String.format( "There %s %s %s%s", verb, number, candidate, pluralModifier );
    }

    private void createPluralDependentMessageParts(int count) { if (count == 0) {
        thereAreNoLetters();
    } else if (count == 1) {
        thereIsOneLetter();
    } else {
        thereAreManyLetters(count); }
    }

    private void thereAreManyLetters(int count) {
        number = Integer.toString(count);
        verb = "are";
        pluralModifier = "s";
    }
    private void thereIsOneLetter() {
        number = "1";
        verb = "is";
        pluralModifier = "";
    }
    private void thereAreNoLetters() {
        number = "no";
        verb = "are";
        pluralModifier = "s";
    }
}
