using System.Collections.Generic;

namespace Breakout.Levels { 
    public class LevelData {
        private TextFileReader levelReader = new TextFileReader ();

        /// <summary>
        /// Reads the Map data and adds each line to a list of strings
        /// </summary>
        /// <param name="fileName">A string</param>
        /// <returns>A string list</returns>
        public List<string> Map (string fileName) {
            List <string> level = levelReader.LevelRead (fileName);
            List <string> map = new List<string> ();
            int Startindex = level.IndexOf ("Map:");
            int Endindex = level.IndexOf ("Map/");
            for (int i = Startindex+1; i < Endindex; i++) {
                map.Add (level[i]);
            }
            return map;
        }

        /// <summary>
        /// Reads the meta data and adds each line to a list of strings
        /// </summary>
        /// <param name="fileName">A string</param>
        /// <returns>A string list</returns>
        public List<string> Meta (string fileName) {
            List <string> level = levelReader.LevelRead (fileName);
            List<string> meta = new List<string> ();
            int Startindex = level.IndexOf ("Meta:");
            int Endindex = level.IndexOf ("Meta/");
            for (int i = Startindex+1; i < Endindex; i++) {
                meta.Add (level[i]);
            }
            return meta;
        }
        
        /// <summary>
        /// Reads the legend data and adds each line to a list of strings
        /// </summary>
        /// <param name="fileName">A string</param>
        /// <returns>A string list</returns>
        public List<string> Legend (string fileName) {
            List <string> level = levelReader.LevelRead (fileName);
            List<string> legend = new List<string> ();
            int Startindex = level.IndexOf ("Legend:");
            int Endindex = level.IndexOf ("Legend/");
            for (int i = Startindex+1; i < Endindex; i++) {
                legend.Add (level[i]);
            }
            return legend;
        }
    }
}