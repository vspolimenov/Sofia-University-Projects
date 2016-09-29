using System;

namespace PractucumOOPProject
{
    public class Player : IPlayerMovements
    {
        private int playerMarker = 0;
        private int numberOfMarkedPossition = 1;
        private string name = null;

        private void IsFulChecking(Terrain currentTerrain)
        {
            currentTerrain.IsFull = true;
            for (int l = 0; l < currentTerrain.SizeOfTheMatrix; l++)
            {
                for (int j = 0; j < currentTerrain.SizeOfTheMatrix; j++)
                {
                    if (currentTerrain.TerrainMatrix[l, j] == 0)
                    {
                        Console.WriteLine("{0} {1}",l, j);
                        currentTerrain.IsFull = false;
                    }
                }
            }
            Console.WriteLine(currentTerrain.IsFull);
        }
        public Player(string name, int playerMarker)
        {
            this.Name = name;
            if (playerMarker > 2)
            {
                this.PlayerMarker = playerMarker;
            }
            else
            {
                throw new ArgumentException("Marker must be > 2");
            }
            
        }
        public void GenerateMovements(Terrain currentTerrain)
        {
            Console.WriteLine("Number of movements (1-3): ");
            int numberOfMovements = int.Parse(Console.ReadLine());
            for (int i = 0; i < numberOfMovements; i++)
            {

                IsFulChecking(currentTerrain);

                if (currentTerrain.IsFull)
                {
                    return;
                }

                Console.WriteLine("Enter the row of the new possition ");
                int newRow = int.Parse(Console.ReadLine());

                Console.WriteLine("Enter the col of the new possition ");
                int newCol = int.Parse(Console.ReadLine());

                bool isLegalPossition = currentTerrain.TerrainMatrix[newRow, newCol] == 0 && (((newRow == 0 && currentTerrain.TerrainMatrix[newRow, newCol - 1] == PlayerMarker || currentTerrain.TerrainMatrix[newRow, newCol + 1] == PlayerMarker)
                    || currentTerrain.TerrainMatrix[newRow - 1, newCol] == PlayerMarker )||
                                    ((newRow == currentTerrain.SizeOfTheMatrix -1 && currentTerrain.TerrainMatrix[newRow, newCol - 1] == PlayerMarker || currentTerrain.TerrainMatrix[newRow, newCol + 1] == PlayerMarker)
                                    || currentTerrain.TerrainMatrix[newRow + 1, newCol] == PlayerMarker) ||
                                       ((newCol== 0 && currentTerrain.TerrainMatrix[newRow - 1, newCol ] == PlayerMarker || currentTerrain.TerrainMatrix[newRow + 1, newCol ] == PlayerMarker) || currentTerrain.TerrainMatrix[newRow, newCol - 1] == PlayerMarker) ||
                                       ( (newCol == currentTerrain.SizeOfTheMatrix - 1 && currentTerrain.TerrainMatrix[newRow, newCol - 1] == PlayerMarker || currentTerrain.TerrainMatrix[newRow, newCol + 1] == PlayerMarker) ||
                                        currentTerrain.TerrainMatrix[newRow, newCol + 1] == PlayerMarker));


                if (isLegalPossition && currentTerrain.IsFull == false)
                {
                  
                    currentTerrain.TerrainMatrix[newRow, newCol] = PlayerMarker;
                    numberOfMarkedPossition++;
                }

                else if (currentTerrain.IsFull)
                {
                    return;
                }

                else
                {

                    throw new ArgumentException("Illegal possition!");
                }
                GameManager.DisplayTerrain(currentTerrain);
            }
        }

        public int PlayerMarker
        {
            get
            {
                return playerMarker;
            }
            set
            {
                if (value > 2)
                {
                    this.playerMarker = value;
                }
                else
                {
                    throw new ArgumentException("Marker must be > 2");
                }
            }
        }

        public string Name
        {
            get
            {
                return name;
            }

            set
            {
                name = value;
            }
        }
        public int NumberOfMarkedPossition
        {
            get
            {
                return numberOfMarkedPossition;
            }
        }
    }
}