using DIKUArcade.Math;
using System;
using System.Collections.Generic;

namespace Breakout.Levels { 
    public class Map {
        private LevelData levelData = new LevelData ();
        private List<Tuple<Vec2F,char>> Coord_Sign = new List<Tuple<Vec2F,char>> ();
        
        ///<summary>
        /// Reads the map information of a given level from levelData.
        /// </summary>
        /// <param name="fileName">A string</param>
        /// <returns>A list of strings</returns>
        public List<Tuple<Vec2F,char>> MapReader (string fileName) {
            for (int i = 0; i < levelData.Map(fileName).Count; i++) {
                string row = levelData.Map(fileName)[i];
                float y = (1.00f / (float)levelData.Map(fileName).Count);               
                float x = (1.00f / (float)row.Length);
                for (int j = 0; j < row.Length; j++) {                
                    if (row[j] != '-') {
                        Coord_Sign.Add (new Tuple<Vec2F,char> (new Vec2F ((x * (float)j), 0.96f - (y * (float)i)), row[j]));
                    }
                }
            }
            return Coord_Sign;
        }
    }
}
