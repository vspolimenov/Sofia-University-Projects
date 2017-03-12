using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PractucumOOPProject
{
    class Program
    {
        static void Main(string[] args)
        {

            Player firstPlayer = new Player("Vasko", 3);
            ComputerPlayerLogic1 secondPlayer = new ComputerPlayerLogic1();
            ComputerPlayerLogic2 thirdPlayer = new ComputerPlayerLogic2();

            GameManager.DisplayMenu();





            int userInput = int.Parse(Console.ReadLine());

            if (userInput == 1)
            {
                Console.WriteLine("\t\t Enter the size of the terrain. Must be > 2!");
                int sizeOfTheTerrain = int.Parse(Console.ReadLine());
                while (sizeOfTheTerrain <= 2)
                {
                    Console.WriteLine("\t\t Enter the size of the terrain. Must be > 2!");
                    sizeOfTheTerrain = int.Parse(Console.ReadLine());
                }

                Terrain currentTerrain = new Terrain(sizeOfTheTerrain);
                GameManager.GeneratePlayersInTheTerrain(firstPlayer, secondPlayer, currentTerrain);


                GameManager.DisplayTerrain(currentTerrain);
                do
                {

                    firstPlayer.GenerateMovements(currentTerrain);
                    secondPlayer.GenerateMovements(currentTerrain);
                    GameManager.DisplayTerrain(currentTerrain);

                    if (currentTerrain.IsFull)
                    {
                        GameManager.DisplayTerrain(currentTerrain);
                        GameManager.DisplayResults(firstPlayer, secondPlayer);
                        break;
                    }
                }
                while (currentTerrain.IsFull == false);
            }
            else if (userInput == 2)
            {
                Console.WriteLine("\t\t Enter the size of the terrain");
                int sizeOfTheTerrain = int.Parse(Console.ReadLine());
                Terrain currentTerrain = new Terrain(sizeOfTheTerrain);
                GameManager.GeneratePlayersInTheTerrain(firstPlayer, secondPlayer, currentTerrain);

                GameManager.DisplayTerrain(currentTerrain);
                do
                {

                    firstPlayer.GenerateMovements(currentTerrain);
                    thirdPlayer.GenerateMovements(currentTerrain);
                    GameManager.DisplayTerrain(currentTerrain);

                    if (currentTerrain.IsFull)
                    {
                        GameManager.DisplayTerrain(currentTerrain);
                        GameManager.DisplayResults(firstPlayer, thirdPlayer);
                        break;
                    }

                }
                while (currentTerrain.IsFull == false);
            }
            if (userInput == 3)
            {
                Console.WriteLine("Enter the name of the player");
                string name = Console.ReadLine();
                Player newPlayer = new Player(name, 4);
                Console.WriteLine("\t\t Enter the size of the terrain");
                int sizeOfTheTerrain = int.Parse(Console.ReadLine());
                Terrain currentTerrain = new Terrain(sizeOfTheTerrain);
                GameManager.GeneratePlayersInTheTerrain(firstPlayer, newPlayer, currentTerrain);

                GameManager.DisplayTerrain(currentTerrain);
                do
                {

                    firstPlayer.GenerateMovements(currentTerrain);
                    newPlayer.GenerateMovements(currentTerrain);
                    GameManager.DisplayTerrain(currentTerrain);

                    if (currentTerrain.IsFull)
                    {
                        GameManager.DisplayTerrain(currentTerrain);
                        GameManager.DisplayResults(firstPlayer, newPlayer);
                        break;
                    }
                }
                while (currentTerrain.IsFull == false);

            }
        }
    }
}