using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PractucumOOPProject
{
  public  class ComputerPlayerLogic1 : IPlayerMovements
    {
        private int numberOfMarkedPossition = 1;
        public int PlayerMarker
        {
            get
            {
                return 1;
            }
        }

     public string Name
        {
            get
            {
                return "Claus ";
            }
        }
        //Starts from down
        private void GenerateNewPossition(Terrain currentTerrain)
        {
            for (int row = 0; row < currentTerrain.SizeOfTheMatrix; row++)
            {
                for (int col = 0; col < currentTerrain.SizeOfTheMatrix; col++)
                {
                    if (currentTerrain.TerrainMatrix[row, col] == PlayerMarker)
                    {
                        if (row > 0 && currentTerrain.TerrainMatrix[row - 1, col] == 0)
                        {
                            currentTerrain.TerrainMatrix[row - 1, col] = PlayerMarker;
                            numberOfMarkedPossition++;
                            return;
                        }

                        else if (row < currentTerrain.SizeOfTheMatrix - 1 && currentTerrain.TerrainMatrix[row + 1, col] == 0)
                        {
                            currentTerrain.TerrainMatrix[row + 1, col] = PlayerMarker;
                            numberOfMarkedPossition++;
                            return;
                        }

                        else if (col < currentTerrain.SizeOfTheMatrix - 1 && currentTerrain.TerrainMatrix[row, col + 1] == 0)
                        {
                            currentTerrain.TerrainMatrix[row, col + 1] = PlayerMarker;
                            numberOfMarkedPossition++;
                            return;
                        }

                        else if (col > 0 && currentTerrain.TerrainMatrix[row, col - 1] == 0)
                        {
                            currentTerrain.TerrainMatrix[row, col - 1] = PlayerMarker;
                            numberOfMarkedPossition++;
                            return;
                        }

                        else if(currentTerrain.IsFull == false)
                        {
                            currentTerrain.IsFull = true;
                            for (int i = 0; i < currentTerrain.SizeOfTheMatrix; i++)
                            {
                                for (int j = 0; j < currentTerrain.SizeOfTheMatrix; j++)
                                {
                                    if (currentTerrain.TerrainMatrix[i, j] == 0)
                                    {
                                        currentTerrain.IsFull = false;
                                    }
                                }
                                continue;
                            }
                        }
                        
                        else if(currentTerrain.IsFull)
                        {
                            return;
                        }
                       
                  
                    }
                }
            }
    }
        public void GenerateMovements(Terrain currentTerrain)
        {
            for (int i = 0; i < 3; i++)
            {
                if (currentTerrain.IsFull)
                {
                    return;
                }
                GenerateNewPossition(currentTerrain);
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
