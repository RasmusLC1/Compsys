using System.IO;
using System.Collections.Generic;

namespace Breakout.Levels { 
    public class LevelDictionary {
        public Dictionary<int, string> leveldata = new Dictionary<int, string>();
        int n;
        int index;

        /// <summary>
        /// Gets the filenames of txt documents in a given directory and removes the
        /// file extension from the name
        /// </summary>
        /// <returns>A dictionary with key of int value from 0 to dictionary length and value of filename</returns>
        public Dictionary<int, string> GetFileNames() {
           n = 0;
           leveldata.Clear();
           DirectoryInfo Folder = new DirectoryInfo (Path.Combine("Assets", "Levels"));
           FileInfo[] Files = Folder.GetFiles("*.txt");
           foreach (FileInfo item in Files) {
               if (item.Name != ".txt"){ //Added to make the tests run due to path error
                   index = item.Name.IndexOf(".");
                   leveldata.Add(n, item.Name.Remove(index));
                   n++;
               }
               
           }
           return leveldata;
        }
    }
}