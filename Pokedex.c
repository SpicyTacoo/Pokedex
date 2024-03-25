#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Pokemon
{
    char name[21];
    char type[10];
    char description[51];
    int seen;
    int defeated;
};

void initializeIndexNull(struct Pokemon pokemonData[]);
void initializeProgressZero(struct Pokemon pokemonData[]);
int checkLatestEmptyIndex(struct Pokemon pokemonData[]);
int checkDuplicateEntries(struct Pokemon pokemonData[], int index);
int checkFirstIndex(struct Pokemon pokemonData[]);
void addEntry(struct Pokemon pokemonData[]);
void modifyEntry(struct Pokemon pokemonData[]);
void deleteEntry(struct Pokemon pokemonData[]);
void displayAllEntries(struct Pokemon pokemonData[]);
void searchPokemonByName(struct Pokemon pokemonData[]);
void searchPokemonByType(struct Pokemon pokemonData[]);
void displayEntryByTypeOrName(struct Pokemon pokemonData[], int index);
void export(struct Pokemon pokemonData[], FILE* writeFile);
void import(struct Pokemon pokemonData[], FILE* readFile);
int exitDataManageMenu();
void researchTasks(struct Pokemon pokemonData[]);
void reviewResearchTypePokemon(struct Pokemon pokemonData[]);
void reviewResearchTypeTaskType(struct Pokemon pokemonData[]);
void updateResearchTask(struct Pokemon pokemonData[]);
int exitResearchTask();



int main(){
    struct Pokemon pokemonData[150];
    FILE *fp;
    int pokedexChoices;
    int deleteIndex;
    int startPokedex = 1;
    char key[50];

    initializeIndexNull(pokemonData); // call initializeIndexNull function
    initializeProgressZero(pokemonData); // call initializeProgressZero function

    do
    {
        printf("\n\nWelcome Fellow Pokemon Trainer!\n\n");
        printf("* [1] Add Entry\n");
        printf("* [2] Modify Entry\n");
        printf("* [3] Delete Entry\n");
        printf("* [4] Display All Entry\n");
        printf("* [5] Search Pokemon by Name\n");
        printf("* [6] Search Pokemon by Type\n");
        printf("* [7] Export\n");
        printf("* [8] Import\n");
        printf("* [9] Research Task Menu\n");
        printf("* [10] Exit\n");
        printf("\nWhat would you like to do?: ");
        scanf("%d", &pokedexChoices);

        
        if (pokedexChoices == 1)
            addEntry(pokemonData); // calls addEntry function
        if (pokedexChoices == 2)
            modifyEntry(pokemonData); // calls modifyEntry function
        if (pokedexChoices == 3)
            deleteEntry(pokemonData); // calls deleteEntry function
        if (pokedexChoices == 4)
            displayAllEntries(pokemonData); // calls displayAllEntries function
        if (pokedexChoices == 5)
            searchPokemonByName(pokemonData); // calls searchPokemonByName function
        if (pokedexChoices == 6)
            searchPokemonByType(pokemonData); // calls searchPokemonByType function
        if (pokedexChoices == 7)
            export(pokemonData, fp); // calls export function
        if (pokedexChoices == 8)
            import(pokemonData, fp); // calls import function
        if (pokedexChoices == 9)
            researchTasks(pokemonData); // calls researchTasks function
        if (pokedexChoices == 10)
            startPokedex = exitDataManageMenu(startPokedex); // calls exitDataManageMenu function then store the value to startPokedex variable

        if (!(pokedexChoices >= 1 && pokedexChoices <= 10))
            printf("Invalid Input! Please Enter Valid Choice!\n\n");

        if (pokedexChoices >= 1 && pokedexChoices <= 9){
            printf("\nInput any key to continue: "); // for better readability on command prompt before looping Data Manage Menu
            scanf("%s", key);
            printf("\n\n\n\n\n");
        }
    } while (startPokedex == 1 || !(pokedexChoices >= 1 && pokedexChoices <= 10));
    printf("\n\nBye! See you next time!");

    return 0;
}

// initializeIndexNull initializes all index with null character for it to be easier to find empty index.
void initializeIndexNull(struct Pokemon pokemonData[])
{
    for (int i = 0; i < 150; i++) {
        strcpy (pokemonData[i].name, "\0");
        strcpy (pokemonData[i].type, "\0");
        strcpy (pokemonData[i].description, "\0");
    }
}

// initializeProgressZero initializes 0 for all index's research progress.
void initializeProgressZero(struct Pokemon pokemonData[])
{
    for (int i = 0; i < 150; i++)
    {
        pokemonData[i].seen = 0;
        pokemonData[i].defeated = 0;
    }
}

/* checkLatestEmptyIndex loops to check for the latest empty index.

    @return index(i) of an array as soon as it finds an empty index (the index with the null char), -1 if there are no empty index. 
*/
int checkLatestEmptyIndex(struct Pokemon pokemonData[])
{
    char temp[21];

    for (int i = 0; i < 150; i++)
    {
        //if (strcmp(pokemonData[i].name, "\0") == 1) // testing
        strcpy(temp, pokemonData[i].name);
        if (temp[0] == '\0')
            return i;
    }
    return -1;
}

/* displayAllEntries shows all non-empty entries. It first calls checkLatestEmptyIndex to find the latest empty index.
    It then loops until just before the empty index. If all index are empty, user would be prompted to add pokemon/s first,
    before being able to use this feature.
*/
void displayAllEntries(struct Pokemon pokemonData[])
{
    int latestEmptyIndex, i;

    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no Pokemon yet! Please add some first. \n");
        return;
    }

    latestEmptyIndex = checkLatestEmptyIndex(pokemonData);

    printf("\n\nAll Added Pokemons: \n\n");
    for (i = 0; i < latestEmptyIndex; i++)
    {
        printf("%d\n\t", i + 1);
        printf("%s\n\t", pokemonData[i].name);
        printf("%s\n\t", pokemonData[i].type);
        printf("%s\n\n", pokemonData[i].description);
    }
    
}

/* addEntry let user add Pokemon/s. The user will be able input the Pokemon's name, type, and description. 
    Lastly, user will be asked if he/she would like to add another Pokemon again and again, 
    until the user wants to stop or until there are no more slots. 
*/
void addEntry(struct Pokemon pokemonData[])
{
    int reply = 0;

    do{
        int emptyIndex, i;
        char tempType[10];
        emptyIndex = checkLatestEmptyIndex(pokemonData);

        if (emptyIndex == -1){
            printf("\nThere are no more available slots! You may delete some Pokemons.\n");
            return;
        }

        do{
            printf("\n\nName: ");
            scanf("%s", pokemonData[emptyIndex].name);

            if (checkDuplicateEntries(pokemonData, emptyIndex) == 1)
                printf("Pokemon already exist! Please enter another Pokemon.\n\n");
            if (strlen(pokemonData[emptyIndex].name) > 20)
                printf("Exceeded Maximum Letters!\n\n");
        } while(checkDuplicateEntries(pokemonData, emptyIndex) == 1 || strlen(pokemonData[emptyIndex].name) > 20);
    

        do{
            printf("Type: ");
            scanf("%s", tempType);
            for(i = 0; tempType[i]; i++) 
                tempType[i] = tolower(tempType[i]);
            
            if (strcmp(tempType, "water") != 0)
                if (strcmp(tempType, "fire") != 0)
                    if (strcmp(tempType, "grass") != 0)
                        if (strcmp(tempType, "electric") != 0)
                            printf("Invalid Type!\n\n");
        } while (!(strcmp(tempType, "water") == 0 || strcmp(tempType, "fire") == 0 || strcmp(tempType, "grass") == 0 || strcmp(tempType, "electric") == 0) != 0);
        strcpy(pokemonData[emptyIndex].type, tempType);


        do{
            printf("Description: "); 
            scanf(" %50[^\n]", pokemonData[emptyIndex].description);

            if (strlen(pokemonData[emptyIndex].description) > 50)
                printf("Exceeded Maximum Letters!\n\n");
        } while (strlen(pokemonData[emptyIndex].description) > 50);

        do{
            printf("\nDo you want to add another Pokemon entry? [0] No, [1] Yes: ");
            scanf("%d", &reply);
            if (reply < 0 || reply > 1)
                printf("Enter 0 or 1 only!\n");
        } while (reply < 0 || reply > 1); // confirm if input is 1 or 0;

    } while (reply == 1);

} 

/* checkDuplicateEntries loops all indexes to check current user input if it is a duplicate Pokemon.
    @param currentInputIndex - current index of user's input.

    @return 1 if current input is already available in other entries and returns 0 if the input is unique.
*/
int checkDuplicateEntries(struct Pokemon pokemonData[], int currentInputIndex)
{
    int i, counter = 0;
    for (i = 0; i < 150; i++)
    {
        if (strcmp(pokemonData[currentInputIndex].name, pokemonData[i].name) == 0)
        {
            counter++;
            if (counter == 2)
                return 1;
        }
    }
    return 0;
}

/* checkFirstIndex checks if the first Pokedex entry or index is empty.

    @return 1 if it is empty and return 0 if it is not empty.
*/
int checkFirstIndex(struct Pokemon pokemonData[])
{
    char tempName[21];
    strcpy(tempName, pokemonData[0].name);

    if (tempName[0] == '\0')
        return 1;
    else
        return 0;
}

/* modifyEntry let users change previously added Pokemon's data (name, type, or description).
    If there are no Pokemon data available, user will not be able to use the modify feature.
*/
void modifyEntry(struct Pokemon pokemonData[])
{
    int inputEntry, inputDataUpdate, i;
    char tempType[10]; // temporary placement for Pokemon type

    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no Pokemon available to be modified! \n");
        return;
    }

    displayAllEntries(pokemonData); //display all available entries;
    printf("Which entry do you want to modify?: ");
    scanf("%d", &inputEntry);

    // 6 > 5 + 1 
    if (inputEntry <= 0 || inputEntry >= checkLatestEmptyIndex(pokemonData) + 1) // checks if user input is valid
    {
        printf("Invalid Pokedex Entry! Returning Back To Data Manage Menu.\n\n");
        return;
    }
    
    do
    {
        printf("\nWhich data do you want to modify?\n");
        printf("[1] - Name\n");
        printf("[2] - Type\n");
        printf("[3] - Description\n");
        printf("(Choose 1, 2, or 3): ");
        scanf("%d", &inputDataUpdate);

        if (!(inputDataUpdate >= 1 && inputDataUpdate <= 3))
            printf("Invalid Input! Enter 1, 2, or 3 Only. \n\n");
    } while (!(inputDataUpdate >= 1 && inputDataUpdate <= 3));
    
    
    if (inputDataUpdate == 1)
    {
        do {
            printf("\n\nName: ");
            scanf("%s", pokemonData[inputEntry - 1].name);

            if (checkDuplicateEntries(pokemonData, inputEntry - 1) == 1)
                printf("Pokemon already exist! Please enter another Pokemon.\n\n");
            if (strlen(pokemonData[inputEntry - 1].name) > 20)
                printf("Exceeded Maximum Letters!\n\n");
        } while (checkDuplicateEntries(pokemonData, inputEntry - 1) == 1 || strlen(pokemonData[inputEntry - 1].name) > 20);
    }

    if (inputDataUpdate == 2)
    {
        do {
            printf("\n\nType: ");
            scanf("%s", tempType);
            for(i = 0; tempType[i]; i++)
                tempType[i] = tolower(tempType[i]);

            if (strcmp(tempType, "water") != 0)
                if (strcmp(tempType, "fire") != 0)
                    if (strcmp(tempType, "grass") != 0)
                        if (strcmp(tempType, "electric") != 0)
                            printf("Invalid Type!\n\n");
        } while (!(strcmp(tempType, "water") == 0 || strcmp(tempType, "fire") == 0 || strcmp(tempType, "grass") == 0 || strcmp(tempType, "electric") == 0) != 0);
        strcpy(pokemonData[inputEntry - 1].type, tempType);
    }

    if (inputDataUpdate == 3)
    {
        do {
            printf("\n\nDescription: ");
            scanf(" %50[^\n]", pokemonData[inputEntry - 1].description);

            if (strlen(pokemonData[inputEntry - 1].description) > 50) 
                printf("Exceeded Maximum Letters!\n\n");
        } while (strlen(pokemonData[inputEntry - 1].description) > 50);
    }

    if (inputDataUpdate == 1)
        printf("Entry Number %d's Name Has Been Successfully Updated!\n", inputEntry);
    if (inputDataUpdate == 2)
        printf("Entry Number %d's Type Has Been Successfully Updated!\n", inputEntry);
    if (inputDataUpdate == 3)
        printf("Entry Number %d's Description Has Been Successfully Updated!\n", inputEntry);
}

/* deleteEntry asks user to input the entry to be deleted. 
    Every entry after the inputed entry will be moved one index forward until the last index is left. 
    The last index would be initialized with null characther. 
*/
void deleteEntry(struct Pokemon pokemonData[])
{
    int deleteIndex, latestEmptyIndex;
    
    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no Pokemon available to be deleted!. \n");
        return;
    }

    latestEmptyIndex = checkLatestEmptyIndex(pokemonData); //stores latest empty index
    displayAllEntries(pokemonData); // display all available entries

    do // ask user for input then check if user input is valid
    {
        printf("Which entry do you want to Delete: ");
        scanf("%d", &deleteIndex);

        if (deleteIndex <= 0 || deleteIndex > latestEmptyIndex) 
            printf("Invalid Entry! Please enter valid entry or non-empty entry.\n\n");
    } while(deleteIndex <= 0 || deleteIndex > latestEmptyIndex);
    

    for (int i = deleteIndex; i < 150; i++)
    {
        strcpy(pokemonData[i - 1].name, pokemonData[i].name);
        strcpy(pokemonData[i - 1].type, pokemonData[i].type);
        strcpy(pokemonData[i - 1].description, pokemonData[i].description);
    }
    strcpy(pokemonData[149].name, "\0");
    strcpy(pokemonData[149].type, "\0");
    strcpy(pokemonData[149].description, "\0");
}

/* searchPokemonByName will let users search for Pokemon/s with the user's inputted word containing 2 - 20 letters. 
    if there are no Pokemon data available, user would not be able to use this feature. At the same time user 
    will be asked to add pokemon/s before using this feature. If there are no matches user would be prompted there 
    are no matches for the inputted word.
*/
void searchPokemonByName(struct Pokemon pokemonData[])
{
    int i, j, k, nameCounter = 0, check = 0;
    char wordSearch[21];
    char namePokemon[21];
    char temp[21];

    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no Pokemon available! Please add a Pokemon before searching for one. \n");
        return;
    }

    do // ask user for input then check if valid, if not user will need to input again until the user input is valid.
    {
        printf("\n\nEnter word to search for Pokemon/s: ");
        scanf("%s", wordSearch);

        if (strlen(wordSearch) <= 1 || strlen(wordSearch) >= 21)
            printf("The word \"%s\" is too long or too short! Please enter words containing 2 - 20 letters.\n\n", wordSearch);
    } while (strlen(wordSearch) <= 1 || strlen(wordSearch) >= 21);
    

    for(i = 0; i < 150; i++)
    {
        strcpy(namePokemon, pokemonData[i].name);

        if (strlen(namePokemon) > strlen(wordSearch))
        {
            for(j = 0; j < strlen(namePokemon) - strlen(wordSearch) + 1; j++)
            {
                for (k = 0; k < strlen(wordSearch); k++)
                    temp[k] = namePokemon[k + j];
                if (strcmp(temp, wordSearch) == 0) //(namePokemon[j], wordSearch[j])
                {
                    displayEntryByTypeOrName(pokemonData, i);
                    j = strlen(namePokemon) - strlen(wordSearch) + 1;
                    nameCounter++;
                }
                
            }
        }
    }

    if (nameCounter == 0)
        printf("0  Matches Found for the Word \"%s\". Returning Back to Data Menu\n\n", wordSearch);
    else
        printf("%d Match/es Found for the Word \"%s\".\n\n", nameCounter, wordSearch);
}

/* searchPokemonByType let users search within the Pokemon data for Pokemon's type (water, fire, grass, or electric).
    User will input a type then this function will search and display all Pokemon/s with the type the user wants to find. 
    If there are no Pokemon data to begin with the user will not be able to use this feature and will be asked to
    add Pokemon before using this feature.
*/
void searchPokemonByType(struct Pokemon pokemonData[])
{
    int i, j, counter = 0;
    char typePokemon[10];

    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no Pokemon available! Please add a Pokemon before searching for one. \n");
        return;
    }

    printf("\n\nEnter the type of Pokemon you want to search for (Water, Fire, Grass, or Electric): ");
    scanf("%s", typePokemon);
    for(i = 0; typePokemon[i]; i++)
        typePokemon[i] = tolower(typePokemon[i]);

    if (!(strcmp(typePokemon, "water") == 0 || strcmp(typePokemon, "fire") == 0 || strcmp(typePokemon, "grass") == 0 || strcmp(typePokemon, "electric") == 0) != 1)
    {
        for (j = 0; j < 150; j++){
            if (strcmp(pokemonData[j].type, typePokemon) == 0) {
                displayEntryByTypeOrName(pokemonData, j);
                counter++;
            }
        }
    }

    else
    {
        printf("\n\nInvalid Type! Returning Back to Data Menu.\n");
        return;
    }

    if (counter == 0)
        printf("\nNo match is found for %s type Pokemon.\n\n", typePokemon);
    else
        printf("\nThese are all of the %s type Pokemon.\n\n", typePokemon);
}

void displayEntryByTypeOrName(struct Pokemon pokemonData[], int index)
{
    printf("\n\n%d\n\t", index + 1);
    printf("%s\n\t", pokemonData[index].name);
    printf("%s\n\t", pokemonData[index].type);
    printf("%s\n\n", pokemonData[index].description);
}

/* export let users save all Pokemon data to a text file.
    User will be first asked what name would they like 
    for the file.
*/
void export(struct Pokemon pokemonData[], FILE* writeFile)
{
    int latestEmptyIndex, i, j, check = 0;
    char fileName[31];
    char tempCheck[5];

    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no Pokemon available to be saved! Please add some Pokemons. \n");
        return;
    }

    do
    {
        printf("\n\nWhat name would you like to name your file? (Please Include \".txt\" at The End): ");
        scanf("%s", fileName);

        for (i = 0; i < 4; i++)
            tempCheck[i] = fileName[strlen(fileName) - 4 + i];
        // printf("%s", tempCheck); //checking
        if (strlen(fileName) >= 31 )
            printf("The file name is too long ! There is a maximum of 30 letters including .txt .\n\n");
        if (strlen(fileName) < 5 || strcmp(tempCheck, ".txt") != 0)
            printf("You forgot to include .txt at the end of the file! Or, \".txt\" is not all in lowercase. Please re-enter a valid file name.\n\n");
        check = strlen(fileName);
    } while (check <= 5 || check >= 31);

    latestEmptyIndex = checkLatestEmptyIndex(pokemonData);

    writeFile = fopen(fileName, "w");

    for (j = 0; j < latestEmptyIndex; j++)
    {
        fprintf(writeFile, "Name: %s\n", pokemonData[j].name);
        fprintf(writeFile, "Type: %s\n", pokemonData[j].type);
        fprintf(writeFile, "Description: %s\n\n", pokemonData[j].description);
    }
    fclose(writeFile);

    printf("Data has been succesfully saved to \"%s\".\n\n", fileName);
}

/* import let users load available saved text file with a specific format within the file (e.g.):
    name: Pikachu
    type: electric
    description: a yellow, mouse-like creature with electrical abilities.
*/
void import(struct Pokemon pokemonData[], FILE* readFile)
{
    int i, check, counter = 1, answer, latestEmptyIndex = 0, isDuplicate = 0;
    int j, k, l;
    int z, y;
    int a, b, c;
    char fileName[31];
    char tempCheck[5];
    char tempStore[100];
    char tempName[22 + 6];
    char tempType[11 + 6];
    char tempDescription[52 + 13];
    
    do{
        do{
            printf("\n\nWhich file would you like to load? (Please Include \".txt\" at The End): ");
            scanf("%s", fileName);

            for (i = 0; i < 4; i++)
                tempCheck[i] = fileName[strlen(fileName) - 4 + i];
            // printf("%s", tempCheck); //checking
            if (strlen(fileName) >= 31 )
                printf("The file name is too long ! There is a maximum of 30 letters including .txt .\n\n");
            if (strlen(fileName) < 5 || strcmp(tempCheck, ".txt") != 0)
                printf("You forgot to include .txt at the end of the file! Or, \".txt\" is not all in lowercase. Please re-enter a valid file name.\n\n");
            check = strlen(fileName);
        } while (check <= 5 || check >= 31);

        readFile = fopen(fileName, "r");
        if (readFile == NULL)
            printf("File does not exist! Please choose another file.\n\n");
    } while (readFile == NULL);
    

    while (fgets(tempStore, 100, readFile) != NULL){
        tempStore[strcspn(tempStore, "\n")] = 0;

        if (counter % 4 == 1){
            isDuplicate = 0;
            
            for (j = 6; j < strlen(tempStore) + 20; j++){
                if (j < 34){
                    if(j < strlen(tempStore))
                        tempName[j - 6] = tempStore[j];
                    
                    if(j == strlen(tempStore)){
                        tempName[j - 6] = '\0';
                    }
                }
            }

            // printf("\n\nName: %s", tempName);
            for (z = 0; z < 150; z++){
                if (strcmp(tempName, pokemonData[z].name) == 0){
                    isDuplicate = 1;
                    printf("The Pokemon named \"%s\" already exist! It will be skipped.\n\n", tempName);
                    
                }
            }
        }

        if (counter % 4 == 2 && isDuplicate == 0){
            for (k = 6; k < strlen(tempStore); k++)
                tempType[k - 6] = tempStore[k];
            // printf("\nType: %s", tempType);
        }

        if (counter % 4 == 3 && isDuplicate == 0){
            for (l = 13; l < strlen(tempStore); l++)
                tempDescription[l - 13] = tempStore[l];

            printf("\n\nName: %s", tempName);
            printf("\nType: %s", tempType);
            printf("\nDescription: %s\n\n", tempDescription);

            do{
                printf("Do you want to save this entry? [1] Yes, [0] No: ");
                scanf("%d", &answer);

                if(!(answer >= 0 && answer <= 1))
                    printf("Invalid Input!\n\n");
            }while (!(answer >= 0 && answer <= 1));

            if (answer == 1){
                latestEmptyIndex = checkLatestEmptyIndex(pokemonData);
                strcpy(pokemonData[latestEmptyIndex].name, tempName);
                strcpy(pokemonData[latestEmptyIndex].type, tempType);
                strcpy(pokemonData[latestEmptyIndex].description, tempDescription);
                printf("Pokemon has been successfully added!\n");
            }
            for (a = 0; a < 28; a++)
                tempName[a] = 0;
            for (b = 0; b < 17; b++)
                tempType[b] = 0;
            for (c = 0; c < 65; c++)
                tempDescription[c] = 0;
        }
        counter++;
    }

    fclose(readFile);
}

// exitDataManageMenu when called returns a value that will let the user quit Data Manage Menu.
int exitDataManageMenu()
{
    return 0;
}

// researchTasks let users access more features related to Pokemon research tasks.
void researchTasks(struct Pokemon pokemonData[])
{
    int researchTasksChoice, startResearchTask = 1;
    char key[20];

    if (checkFirstIndex(pokemonData) == 1){
        printf("\nThere are no pokemon entries available! Please add a Pokemon before entering Research Tasks Menu. \n\n");
        return;
    }

    do{
        printf("\n\nResearch Task Menu:\n");
        printf("* [1] Review Research Task per Pokemon\n");
        printf("* [2] Review Research Task per Task Type\n");
        printf("* [3] Update Research Task\n");
        printf("* [4] Exit\n\n");
        printf("What would you like to do?: ");
        scanf("%d", &researchTasksChoice);

        if (researchTasksChoice == 1)
            reviewResearchTypePokemon(pokemonData);
        if (researchTasksChoice == 2)
            reviewResearchTypeTaskType(pokemonData);
        if (researchTasksChoice == 3)
            updateResearchTask(pokemonData);
        if (researchTasksChoice == 4)
            startResearchTask = exitResearchTask();
        
        printf("\nInput any key to continue: ");
        scanf("%s", key);
        printf("\n\n\n\n");
        // printf("seen:%d defeated:%d", pokemonData[0].seen, pokemonData[0].defeated);//testing 
    } while(startResearchTask == 1);
}

/* reviewResearchTypePokemon let users decide which non-empty emtry they would like to view it's research progress.
    User will first be shown all available entries, then will be asked to input an entry to view. feature only 
    accessible when there is at least 1 Pokemon data.
*/
void reviewResearchTypePokemon(struct Pokemon pokemonData[])
{
    int entryPokedex;
    displayAllEntries(pokemonData);

    do {
        printf("\nWhich entry do you want to view?: ");
        scanf("%d", &entryPokedex);

        if (entryPokedex <= 0 || entryPokedex >= checkLatestEmptyIndex(pokemonData) + 1)
            printf("Invalid Pokedex Entry! Please Only Enter Entries That Are Available.\n\n");
    } while (entryPokedex <= 0 || entryPokedex >= checkLatestEmptyIndex(pokemonData) + 1);

    printf("Name: %s\n", pokemonData[entryPokedex - 1].name);
    printf("Research Task Progress: %d Seen\n", pokemonData[entryPokedex - 1].seen);
    printf("                        %d Defeated\n\n", pokemonData[entryPokedex - 1].defeated);
}

/* reviewResearchTypeTaskType users decide which research task (seen, defeated) they would like to view for all available Pokemon/s.
    If the research progress for all are zero then user will be prompted that no match is found.
*/
void reviewResearchTypeTaskType(struct Pokemon pokemonData[])
{
    int userInput, emptyIndex, i, counter = 0;

    do{
        printf("\nWhich research task would you like to view?([1] - Seen, [2] - Defeated): ");
        scanf("%d", &userInput);

        if (userInput < 1 || userInput > 2)
            printf("Invalid Input! Please Enter 1 or 2.\n\n");
    }while (userInput < 1 || userInput > 2);

    emptyIndex = checkLatestEmptyIndex(pokemonData);
    
    if (userInput == 1)
    {
        printf("\nList of Pokemon's Seen Progress:\n\n");
        for (i = 0; i < emptyIndex; i++)
        {
            if(pokemonData[i].seen >= 1)
            {
                printf("Name: %s\n", pokemonData[i].name);
                printf("Research Task Progress: %d Seen\n\n", pokemonData[i].seen);
                counter++;
            }
        }
    }
    

    if (userInput == 2)
    {   
        printf("\nList of Pokemon's Deafeated Progress:\n\n");
        for (i = 0; i < emptyIndex; i++)
        {
            if(pokemonData[i].defeated >= 1)
            {
                printf("Name: %s\n", pokemonData[i].name);
                printf("Research Task Progress: %d Defeated\n\n", pokemonData[i].defeated);
                counter++;
            }
        }
    }

    if (counter == 0)
        printf("No match is found!\n\n");
}


/* reviewResearchTypeTaskType users update Pokemon's research task progress.
    User will first be asked to input which research task was completed then 
    will be asked how many was seen or defeated. Input will be added to previous 
    progress. 
*/
void updateResearchTask(struct Pokemon pokemonData[])
{
    int userInput, inputEntry, emptyIndex, updatedAmount;

    do{
        printf("\nWhat research task was completed?([1] - Seen, [2] - Defeated): ");
        scanf("%d", &userInput);

        if (userInput < 1 || userInput > 2)
            printf("Invalid Input! Please Enter 1 or 2.\n\n");
    }while (userInput < 1 || userInput > 2);

    displayAllEntries(pokemonData);

    printf("Which entry do you want to update?: ");
    scanf("%d", &inputEntry);

    if (inputEntry <= 0 || inputEntry >= checkLatestEmptyIndex(pokemonData) + 1)
    {
        printf("Invalid Pokedex Entry! Returning Back To Research Task Menu.\n\n");
        return;
    }

    do {
        if (userInput == 1)
            printf("How many are seen?: ");
        if (userInput == 2)
            printf("How many are defeated?:");
        scanf("%d", &updatedAmount);
        
        if (updatedAmount < 0)
            printf("Invalid Amount!");
    }while (updatedAmount < 0);

    if (userInput == 1)
        pokemonData[inputEntry - 1].seen = pokemonData[inputEntry - 1].seen + updatedAmount;
    if (userInput == 2)
        pokemonData[inputEntry - 1].defeated = pokemonData[inputEntry - 1].defeated + updatedAmount;
    printf("Research Task Has Been Succesfully Updated!\n\n");
}

// exitDataManageMenu when called returns a value that will let the user quit Research Task Menu.
int exitResearchTask()
{
    return 0;
}

