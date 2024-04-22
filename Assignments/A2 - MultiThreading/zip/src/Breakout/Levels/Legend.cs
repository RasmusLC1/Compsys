using System;
using System.Collections.Generic;

namespace Breakout.Levels { 
    public class Legend {
        private LevelData levelData = new LevelData ();
        private List<Tuple<string,char>> image_Sign = new List<Tuple<string,char>> ();
        
        /// <summary>
        /// Reads the legend information of a given map from levelData.
        /// </summary>
        /// <param name="fileName">A string</param> 
        public List<Tuple<string,char>> LegendReader (string fileName) {
            image_Sign.Clear();
            foreach (string element in levelData.Legend(fileName)) {
                image_Sign.Add (new Tuple<string,char> (element.Substring (3), element[0]));
            }
            return image_Sign;
        }
    }
}
