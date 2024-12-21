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
                playBlackjack(currPlayer);
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


void playBlackjack(pemain currPlayer) {
    int playerBet, playerTotal = 0, dealerTotal = 0;
    char choice;
    srand(time(NULL));

    if (currPlayer.cash <= 0) {
        printf("Anda tidak memiliki chip untuk bermain!\n");
        gameMenu(currPlayer); // Kembali ke menu permainan
        return;
    }

    printf("Masukkan taruhan Anda (max %d): ", currPlayer.cash);
    scanf("%d", &playerBet);
    if (playerBet > currPlayer.cash || playerBet <= 0) {
        printf("Taruhan tidak valid!\n");
        gameMenu(currPlayer); // Kembali ke menu permainan
        return;
    }

    currPlayer.cash -= playerBet;
    printf("Taruhan Anda: %d\n", playerBet);

    // Mengacak kartu untuk pemain dan dealer
    playerTotal += rand() % 11 + 1; // Kartu pertama pemain
    playerTotal += rand() % 11 + 1; // Kartu kedua pemain
    dealerTotal += rand() % 11 + 1; // Kartu pertama dealer
    dealerTotal += rand() % 11 + 1; // Kartu kedua dealer

    printf("Total kartu Anda: %d\n", playerTotal);
    printf("Total kartu dealer: %d (satu kartu tertutup)\n", dealerTotal - (dealerTotal % 11)); // Menampilkan satu kartu dealer

    // Pemain dapat memilih untuk 'hit' atau 'stand'
    while (1) {
        printf("Apakah Anda ingin 'hit' (h) atau 'stand' (s)? ");
        scanf(" %c", &choice);
        if (choice == 'h') {
            playerTotal += rand() % 11 + 1; // Menambahkan kartu baru
            printf("Total kartu Anda sekarang: %d\n", playerTotal);
            if (playerTotal > 21) {
                printf("Anda bust! Total Anda melebihi 21.\n");
                currPlayer.profit -= playerBet; // Pemain kalah
                break;
            }
        } else if (choice == 's') {
            break; // Pemain memilih untuk berhenti
        } else {
            printf("Pilihan tidak valid! Silakan pilih 'h' atau 's'.\n");
        }
    }

    // Dealer bermain
    printf("Dealer membuka kartu...\n");
    printf("Total kartu dealer: %d\n", dealerTotal);
    while (dealerTotal < 17) {
        dealerTotal += rand() % 11 + 1; // Dealer menarik kartu
        printf("Total kartu dealer sekarang: %d\n", dealerTotal);
    }

    // Menentukan pemenang
    if (playerTotal > 21) {
        printf("Anda kalah!\n");
    } else if (dealerTotal > 21 || playerTotal > dealerTotal) {
        printf("Selamat! Anda menang!\n");
        currPlayer.profit += playerBet; // Pemain menang
    } else if (playerTotal < dealerTotal) {
        printf("Dealer menang!\n");
        currPlayer.profit -= playerBet; // Pemain kalah
    } else {
        printf("Seri! Taruhan Anda dikembalikan.\n");
    }

    currPlayer.gamePlayed++; // Menambah jumlah permainan yang dimainkan
    printf("Saldo Anda sekarang: %d\n", currPlayer.cash + currPlayer.profit);

    // Menunggu pengguna melihat hasil sebelum kembali ke menu
    printf("\nTekan tombol apa saja untuk kembali ke menu permainan...\n");
    getchar(); // Menangkap karakter newline sebelumnya
    getchar(); // Menunggu input dari pengguna

    // Kembali ke menu permainan
    gameMenu(currPlayer);


}
void playHighOrLow(){

}
void playHeadOrTail(){

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
