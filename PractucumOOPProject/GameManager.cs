using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PractucumOOPProject
{
  public static class GameManager
    {
        public static void DisplayMenu()
        {
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("\t\t\t\t\t\t *** Start ***");
            Console.WriteLine();
            Console.WriteLine("\t\t Press 1 to play against Grigorov ");
            Console.WriteLine("\t\t Press 2 to play against Claus ");
            Console.WriteLine("\t\t Press 3 for 2 players ");
            Console.WriteLine("\t\t Press any other key to exit");
            Console.WriteLine();
        }
        public static void DisplayResults(Player firstPlayer, Player secondPlayer)
        {
            Console.WriteLine("{0}'s Marked possition: {1}", firstPlayer.Name, firstPlayer.NumberOfMarkedPossition);
            Console.WriteLine("{0}'s Marked possition: {1}", secondPlayer.Name, secondPlayer.NumberOfMarkedPossition);
        }

        public static void DisplayResults(Player firstPlayer, ComputerPlayerLogic1 secondPlayer)
        {
            Console.WriteLine("{0}'s Marked possition: {1}", firstPlayer.Name, firstPlayer.NumberOfMarkedPossition);
            Console.WriteLine("{0}'s Marked possition: {1}", secondPlayer.Name, secondPlayer.NumberOfMarkedPossition);
        }

        public static void DisplayResults(Player firstPlayer, ComputerPlayerLogic2 secondPlayer)
        {
            Console.WriteLine("{0}'s Marked possition: {1}", firstPlayer.Name, firstPlayer.NumberOfMarkedPossition);
            Console.WriteLine("{0}'s Marked possition: {1}", secondPlayer.Name, secondPlayer.NumberOfMarkedPossition);
        }
        public static void DisplayResults(ComputerPlayerLogic2 firstPlayer, ComputerPlayerLogic1 secondPlayer)
        {
            Console.WriteLine("{0}'s Marked possition: {1}", firstPlayer.Name, firstPlayer.NumberOfMarkedPossition);
            Console.WriteLine("{0}'s Marked possition: {1}", secondPlayer.Name, secondPlayer.NumberOfMarkedPossition);
        }

        public static void DisplayTerrain(Terrain currentTerrain)
        {
            if (currentTerrain.IsFull)
            {
                return;
            }
            Console.WriteLine();
            Console.WriteLine();

            for (int row = 0; row < currentTerrain.SizeOfTheMatrix; row++)
            {
                Console.Write("\t\t\t");
                for (int col = 0; col < currentTerrain.SizeOfTheMatrix; col++)
                {
                    Console.Write("  |{0}|  ",currentTerrain.TerrainMatrix[row,col]);
                }

                Console.WriteLine();
                Console.WriteLine();
            }
            Console.WriteLine();
            Console.WriteLine();
        }

      public static void GeneratePlayersInTheTerrain(Player firstPlayer, Player secondPlayer, Terrain currentTerrain)
        {
            currentTerrain.TerrainMatrix[0, 0] = firstPlayer.PlayerMarker;
            currentTerrain.TerrainMatrix[currentTerrain.SizeOfTheMatrix - 1, currentTerrain.SizeOfTheMatrix - 1] = secondPlayer.PlayerMarker;
        }
        public static void GeneratePlayersInTheTerrain(Player firstPlayer, ComputerPlayerLogic1 secondPlayer, Terrain currentTerrain)
        {
            currentTerrain.TerrainMatrix[0, 0] = firstPlayer.PlayerMarker;
            currentTerrain.TerrainMatrix[currentTerrain.SizeOfTheMatrix - 1, currentTerrain.SizeOfTheMatrix - 1] = secondPlayer.PlayerMarker;
        }
        public static void GeneratePlayersInTheTerrain(Player firstPlayer, ComputerPlayerLogic2 secondPlayer, Terrain currentTerrain)
        {
            currentTerrain.TerrainMatrix[0, 0] = firstPlayer.PlayerMarker;
            currentTerrain.TerrainMatrix[currentTerrain.SizeOfTheMatrix - 1, currentTerrain.SizeOfTheMatrix - 1] = secondPlayer.PlayerMarker;
        }
        public static void GeneratePlayersInTheTerrain(ComputerPlayerLogic2 firstPlayer, ComputerPlayerLogic1 secondPlayer, Terrain currentTerrain)
        {
            currentTerrain.TerrainMatrix[0, 0] = firstPlayer.PlayerMarker;
            currentTerrain.TerrainMatrix[currentTerrain.SizeOfTheMatrix - 1, currentTerrain.SizeOfTheMatrix - 1] = secondPlayer.PlayerMarker;
        }
    }
}
