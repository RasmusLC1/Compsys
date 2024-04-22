using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace Breakout.Levels {
    public class TextFileReader {
        private List<string> Lines = new List<string> ();

        /// <summary>
        /// Looks for files in effects
        /// </summary>
        /// <param name="filename">filename</param>
        /// <returns>a list of strings from file</returns>
        public List<string> FileReader (string filename) {
            Lines.Clear();
            Lines = File.ReadLines(Path.Combine("Assets", "Effects", filename + ".txt")).ToList();
            return Lines;
        }
        
        /// <summary>
        /// Looks for files in Levels
        /// </summary>
        /// <param name="filename">filename</param>
        /// <returns>a list of strings from file</returns>
        public List<string> LevelRead (string fileName) {
            Lines.Clear();
            Lines = File.ReadLines(Path.Combine("Assets", "Levels", fileName + ".txt")).ToList();
            return Lines;
        }
    }
} 