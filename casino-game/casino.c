#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


struct profilePemain{
    char username[10];
    char password[20];
    char role[10];
    int cash;
    int gamePlayed;
    int profit;
};
typedef struct profilePemain pemain;

pemain users[100];
pemain currPlayer;
int playerIndex;
int totalUsers = 0;

void gameMenu();//parameter profile
void adminMenu();
void mainMenu();
void registrasi();
void loadGame();
void importProfile();
void saveData();

void displayProfile();

void playBlackjack();
void playHighOrLow();
void playHeadOrTail();
void playBarakat();

int searching(const char* cariUsername, const char* cariPassword);

int main(){
    
	importProfile();
    mainMenu();
    
}

void mainMenu(){
	int pilihan;
    //while(1){
    system("cls");
    printf("----------------------------- PROJECT UAS CASINO GACOR -----------------------------\n");
    printf("------------------------------- TEAM TWO NEVER END ---------------------------------\n\n");
	printf("1. New Profile\n");
    printf("2. Load Profile\n");
    printf("0. Exit & Save Progress\n");
    printf("Program: ");
    scanf("%d", &pilihan);
    switch(pilihan){
        case 1:
            //New profile
            registrasi();
            break;
        case 2:
            //Load game profile
            // if( role == 'admin'){
                //adminMenu();
            // }
            loadGame();
            //gameMenu(currPlayer);
            break;
        case 0:
            printf("Keluar game dan menyimpan progress...\n");
            saveData();
            return;
        //default:
    }
    //}
}

void gameMenu(){
    int pilihanGame;
    //while (1) {
        displayProfile(currPlayer);
        printf("\n=== Daftar Game  ===\n");
        printf("0. Info game\n");
        printf("1. Blackjack\n");
        printf("2. High or Low\n");
        printf("3. Head or Tail\n");
        printf("4. Barakat\n");
        printf("5. Back to Main Menu\n");
        printf("Pilih game : ");
        scanf("%d", &pilihanGame);
        switch (pilihanGame) {
            case 0:
                break;
            case 1:
                // playBlackjack();
                break;
            case 2:
                // playHighOrLow();
                break;
            case 3:
                // playHeadOrTail();
                break;
            case 4:
                playBarakat(currPlayer);
                break;
            case 5:
                printf("Kembali ke menu utama...\n");
                mainMenu();
                break;
            default:
                printf("Pilihan tidak valid! masukkan nomor program...\n");
        }
    //}
}

void importProfile(){
	
	FILE* ptr = fopen("akun.txt", "r");
    if (ptr == NULL) {
        printf("no such file.");
        return;
    }
	
    char buf[100];
    while (fscanf(ptr, "%s %s %s %d %d %d ", users[totalUsers].username, 
                  users[totalUsers].password, 
                  users[totalUsers].role, 
                  &users[totalUsers].cash, 
                  &users[totalUsers].gamePlayed, 
                  &users[totalUsers].profit) == 6){
        totalUsers++;    
	}
	fclose(ptr);
}

// Menu untuk admin
void adminMenu(){

}


// Registrasi / membuat akun
void registrasi(){
	char tempUsername[20];
	char tempPassword[20];
	
	printf("Masukkan username baru: ");
	scanf("%20s", tempUsername);
	printf("Masukkan password baru: ");
	scanf("%20s", tempPassword);
	
	if(searching(tempUsername, tempPassword) >= 1){
		printf("Username sudah ada. Gunakan username lain!\n");
		registrasi();
	}else{
		strcpy(users[totalUsers].username, tempUsername);
		strcpy(users[totalUsers].password, tempPassword);
		users[totalUsers].cash = 100;
		users[totalUsers].gamePlayed = 0;
		users[totalUsers].profit = 0;
		totalUsers++;
		printf("\nAkun berhasil dibuat, silahkan login menggunakan username dan password akun yang telah dibuat!\n\n");
		loadGame();
	}
}

// Load profile pemain
void loadGame(){
    char tempUsername[20];
    char tempPassword[20];
    
    printf("Masukkan username: ");
    scanf("%10s", tempUsername); 
    printf("Masukkan password: ");
    scanf("%20s", tempPassword); 

    if (searching(tempUsername, tempPassword) == 1) {
        printf("Profil ditemukan. Selamat datang, %s!\n", tempUsername);
        system("pause");
        currPlayer = users[playerIndex];
        gameMenu(currPlayer);
    } else {
        printf("\nUsername atau password salah.\n\n");
        loadGame();
    }
}

// menampilkan profil singkat pemain
void displayProfile(){
	system("cls");
    printf("| Username: %-10s| Chip: %-9d| Game Played: %-4d| Profit: %-10d|\n", currPlayer.username, currPlayer.cash, currPlayer.gamePlayed, currPlayer.profit);
}


void playBlackjack(){

}
void playHighOrLow(){

}

void playHeadOrTail() {
    char playerChoice[6]; // Head atau Tail
    char computerChoice[6];
    int randomChoice; // untuk menentukan pilihan komputer

    // Menampilkan pilihan untuk pemain
    printf("\n--- Permainan Head or Tail ---\n");
    printf("Pilih 'Head' atau 'Tail': ");
    scanf("%s", playerChoice);

    // Memeriksa apakah pilihan pemain valid
    if (strcmp(playerChoice, "Head") != 0 && strcmp(playerChoice, "Tail") != 0) {
        printf("Pilihan tidak valid! Silakan pilih 'Head' atau 'Tail'.\n");
        playHeadOrTail(); // jika pilihan tidak valid, ulangi permainan
        return;
    }

    // Pilihan acak komputer antara "Head" atau "Tail"
    randomChoice = rand() % 2; // menghasilkan angka 0 atau 1
    if (randomChoice == 0) {
        strcpy(computerChoice, "Head");
    } else {
        strcpy(computerChoice, "Tail");
    }

    // Menampilkan pilihan komputer
    printf("Pilihan komputer: %s\n", computerChoice);

    // Menentukan hasil permainan
    if (strcmp(playerChoice, computerChoice) == 0) {
        printf("Selamat! Anda menang.\n");
        currPlayer.cash += 10; // Menambahkan 10 chip pada pemain
        currPlayer.profit += 10; // Menambahkan 10 pada profit pemain
    } else {
        printf("Sayang sekali, Anda kalah.\n");
        currPlayer.cash -= 5; // Mengurangi 5 chip dari pemain
    }

    // Menambahkan jumlah permainan yang telah dimainkan
    currPlayer.gamePlayed++;

    // Tampilkan profil pemain setelah permainan
    displayProfile();
}

void playBarakat(){
    printf("%s", currPlayer.username);
}


int searching(const char* cariUsername, const char* cariPassword) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(cariUsername, users[i].username) == 0) {
        	if(strcmp(cariPassword, users[i].password) == 0){
        		playerIndex = i;
            	return 1; 
			}
            return 2;
        }
    }
    return 0;
}

void saveData() {
    FILE* ptr = fopen("akun.txt", "w");
    if (ptr == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < totalUsers; i++) {
        fprintf(ptr, "%s %s %s %d %d %d\n", 
                users[i].username, 
                users[i].password, 
                users[i].role, 
                users[i].cash, 
                users[i].gamePlayed, 
                users[i].profit);
    }

    fclose(ptr);
}
