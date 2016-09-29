using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PractucumOOPProject
{
  public  class Terrain
    {
        private int sizeOfTheMatrix = 3;
        private int[,] terainMatrix = new int[100, 100];
        private bool isFull = false;

        public Terrain(int sizeOfTheMatrix)
        {
            if (sizeOfTheMatrix >= this.SizeOfTheMatrix)
            {
                this.SizeOfTheMatrix = sizeOfTheMatrix;
            }
            else
            {
                throw new ArgumentOutOfRangeException();
            }
        }

       public  int [,] TerrainMatrix
        {
            get
            {
                return terainMatrix;
            }
        }
        public int SizeOfTheMatrix
        {
            get
            {
                return sizeOfTheMatrix;
            }

           private set
            {
                sizeOfTheMatrix = value;
            }
        }

     public bool IsFull
        {
            get
            {
                return isFull;
            }

            set
            {
                this.isFull = value;
            }
        }

    }
}
