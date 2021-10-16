#include <iostream>
#include <array>
#include <ctime> 
#include <cstdlib> 
#include <conio.h>
#include <windows.h>

using namespace std;

class Player
{
    int hp = 100;
    int armor = 0;
    int damage = 50;
    int crit = 5;
    int critСhance = 0;
    int money = 0;
    int score = 0;

public:
    void printStat()
    {
        cout << "     Bob statistic:     " << endl;
        cout << "--------------------------" << endl;
        cout << "Hp: " << hp << endl;
        cout << "Armor: " << armor << endl;
        cout << "Damage: " << damage << endl;
        cout << "Crit: " << crit << endl;
        cout << "Money: " << money << endl;
        cout << "Score: " << score << endl;
        cout << "--------------------------" << endl;
    }
    
    int playerDamage()
    {
        return damage + crit;
    }

    void setHp(int Hp)
    {
        this->hp = Hp;
    }

    void setMoney(int Hp)
    {
        this->money = Hp;
    }

    void setScore(int Hp)
    {
        this->score = Hp;
    }
    
    int getHp()
    {
        return hp;
    }

    int getMoney()
    {
        return money;
    }

    int getScore()
    {
        return score;
    }
};

class Enemy
{
    int hp = 100;
    int armor = 0;
    int damage = 50;
    int crit = 5;
    int critСhance = 0;

public:
    void printStat()
    {
        cout << "     Enemy statistic:     " << endl;
        cout << "--------------------------" << endl;
        cout << "Hp: " << hp << endl;
        cout << "Armor: " << armor << endl;
        cout << "Damage: " << damage << endl;
        cout << "crit: " << crit << endl;
        cout << "--------------------------" << endl;
    }

    void setHp(int Hp)
    {
        this->hp = Hp;
    }
    
    int getHp()
    {
        return hp;
    }

    int enemyDamage()
    {
        return damage + crit;
    }
};

class Snake {

    bool gameOver;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score, scoreToWin = 200;
    enum eDiraction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDiraction dir;

    void Setup() {
        gameOver = false;
        dir = STOP;
        x = width / 2 - 1;
        y = height / 2 - 1;
        fruitX = rand() % 18;
        fruitY = rand() % height;
        score = 0;
    }

    void Draw() {
        system("cls");

        for (int i = 0; i <= width; i++)
            cout << "_";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width - 1)
                    cout << "|";
                if (i == y && j == x)
                    cout << "X";
                else if (i == fruitY && j == fruitX)
                    cout << "0";
                else
                    cout << " ";
            }
            cout << endl;
        }
        for (int i = 0; i <= width; i++)
            cout << "_";
        cout << endl;
        cout << "Очки: " << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            }
        }
    }

    void Logic() {
        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        }

        if (x > width - 2 || x < 0 || y > height - 1 || y < 0)
            gameOver = true;
        if (x == fruitX && y == fruitY) {
            score += 100;
            fruitX = rand() % (width - 2);
            fruitY = rand() % height;
        }
    }

    void print(Player player, Enemy enemy)
    {
        player.printStat();
        enemy.printStat();
    }

public:
    bool startGame(Player* player, Enemy enemy)
    {
        int temp;

        Setup();
        while (gameOver == false && score < scoreToWin)
        {
            Draw();
            Input();
            Logic();
        }

        system("cls");

        if (score == scoreToWin)
        {
            enemy.setHp(enemy.getHp() - player->playerDamage());
        }

        if (gameOver == true)
        {
            player->setHp(player->getHp() - enemy.enemyDamage());
        }

        print(*player, enemy);
        system("pause");

        if (enemy.getHp() <= 0)
        {
            player->setMoney(player->getMoney() + 100);
            player->setScore(player->getScore() + 100);
            return 1;
        }

        if (player->getHp() <= 0)
        {
            return 0;
        }

        return startGame(player, enemy);
    }

};

class BlachJack {

    enum CardSuit
    {
        SUIT_CLUB,
        SUIT_DIAMOND,
        SUIT_HEART,
        SUIT_SPADE,
        MAX_SUITS
    };

    enum CardRank
    {
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8,
        RANK_9,
        RANK_10,
        RANK_JACK,
        RANK_QUEEN,
        RANK_KING,
        RANK_ACE,
        MAX_RANKS
    };

    struct Card
    {
        CardRank rank;
        CardSuit suit;
    };

    int getRandomNumber(int min, int max)
    {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

    void shuffleDeck(std::array<Card, 52>& deck)
    {
        for (int index = 0; index < 52; ++index)
        {
            int swapIndex = getRandomNumber(0, 51);
            swap(deck[index], deck[swapIndex]);
        }
    }

    int getCardValue(const Card& card)
    {
        switch (card.rank)
        {
        case RANK_2:    return 2;
        case RANK_3:    return 3;
        case RANK_4:    return 4;
        case RANK_5:    return 5;
        case RANK_6:    return 6;
        case RANK_7:    return 7;
        case RANK_8:    return 8;
        case RANK_9:    return 9;
        case RANK_10:    return 10;
        case RANK_JACK:    return 10;
        case RANK_QUEEN:  return 10;
        case RANK_KING:    return 10;
        case RANK_ACE:    return 11;
        }
        return 0;
    }

    char getPlayerChoice()
    {
        cout << "(h) Взять, or (s) Пас: ";
        char choice = ' ';

        while (choice != 'h' && choice != 's')
        {
          cin >> choice;
        } 

        return choice;
    }

    bool playBlackjack(const array<Card, 52> deck, int* playerTotal)
    {
        const Card* cardPtr = &deck[0];

        int playerTotal_1 = 0;
        int dealerTotal = 0;

        dealerTotal += getCardValue(*cardPtr++);
        cout << "Диллер показывает: " << dealerTotal << '\n';

        playerTotal_1 += getCardValue(*cardPtr++);
        playerTotal_1 += getCardValue(*cardPtr++);

        while (1)
        {
            cout << "У тебя на руках: " << playerTotal_1 << '\n';
            char choice = getPlayerChoice();
            if (choice == 's')
                break;

            playerTotal_1 += getCardValue(*cardPtr++);

            if (playerTotal_1 > 21) {
                *playerTotal = playerTotal_1;
                return false;
            }
        }

        while (dealerTotal < 17)
        {
            dealerTotal += getCardValue(*cardPtr++);
            cout << "У диллера сейчас: " << dealerTotal << '\n';
            Sleep(1000);
        }

        if (dealerTotal > 21) {
            *playerTotal = playerTotal_1;
            return true;
        }

        *playerTotal = playerTotal_1;

        return (playerTotal_1 > dealerTotal);
    }

    void print(Player player, Enemy enemy)
    {
        player.printStat();
        enemy.printStat();
    }

public:
    bool startBlack(Player* player, Enemy enemy) 
    {
        srand(static_cast<unsigned int>(time(0)));
        rand();

        array<Card, 52> deck;

        int playerTotal = 0;
        int card = 0;
        for (int suit = 0; suit < MAX_SUITS; ++suit)
            for (int rank = 0; rank < MAX_RANKS; ++rank)
            {
                deck[card].suit = static_cast<CardSuit>(suit);
                deck[card].rank = static_cast<CardRank>(rank);
                ++card;
            }

        shuffleDeck(deck);

        if (playBlackjack(deck, &playerTotal)) 
        {
            enemy.setHp(enemy.getHp() - player->playerDamage());
            cout << "Ты победил" << endl;
        }
        else 
        {
            player->setHp(player->getHp() - enemy.enemyDamage());
            cout << "У тебя на руках: " << playerTotal << '\n';
            cout << "Ты проиграл" << endl;
        }

        system("pause");
        system("cls");


        print(*player, enemy);
        system("pause");


        if (enemy.getHp() <= 0)
        {
            player->setMoney(player->getMoney() + 100);
            player->setScore(player->getScore() + 100);
            return 1;
        }

        if (player->getHp() <= 0)
        {
            return 0;
        }


        system("cls");
        return startBlack(player, enemy);
    }

};

class Minigames
{
public:

    Snake snake;
    BlachJack black_jack;

    int past_temp = 0;

    int randomGame(Player* player, Enemy enemy) {

        int temp = rand() % 2 + 1;

        if (temp == 1) {
            return snake.startGame(player, enemy);
        }
        if (temp == 2) {
            return black_jack.startBlack(player, enemy);
        }

    }
};

class Room
{
public:
    void RoomChoose()
    {
        system("cls");
        int numOfRooms = rand() % 3 + 1;
        int temp;
        cout << "Выбери комнату!" << endl;

        for (size_t i = 1; i <= numOfRooms; i++)
        {
            cout << i << " ";
        }
        cout << endl;
        cin >> temp;
    }

    bool RoomGeneration(Player* player, Enemy enemy)
    {
        Minigames game;
        int temp = 1;

        switch (temp)
        {
        case 1:
            system("cls");
            cout << "На вас напал враг!" << endl;
            system("pause");
            if (!game.randomGame(player, enemy))
                return 0;
            break;
        case 2:
            //cout << "На вас напал сундук!" << endl;
            break;
        case 3:
            //cout << "На вас напал бомж!" << endl;
            break;
        }
    }
};

class facade
{
    Player player;
    Enemy enemy;
    Room room;

public:
    void menu()
    {
        int temp;
        cout << "1. Начать игру" << endl;
        cout << "2. Выход" << endl;
        cin >> temp;

        switch (temp)
        {
        case 1:
            while (1)
            {
                room.RoomChoose();
                if (room.RoomGeneration(&player, enemy) == 0)
                    break;
            }

            system("cls");
            cout << "Очки: " << player.getScore();
            break;
        case 2:
            return;
            break;
        case 3:            
            break;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    facade start;
    start.menu();

    return 0;
}