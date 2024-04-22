using System;
using System.Collections.Generic;

namespace Breakout.Levels { 
    internal class Meta {
        private LevelData levelData = new LevelData ();
        private Dictionary<char, string> metaBlockDictionary = new Dictionary<char, string> ();
        private TextFileReader effectsDictionary = new TextFileReader ();
        
        /// <summary>
        /// Reads the Meta information of a given map from levelData.
        /// </summary>
        public Dictionary<char, string> MetaReaderBlocks (string fileName) {
            metaBlockDictionary.Clear();
            foreach (string element in levelData.Meta(fileName)) {
                if (effectsDictionary.FileReader("Effects").Contains(element.Substring(0, element.IndexOf(':')))) {
                    string type = element.Substring(0, element.IndexOf(':'));
                    char sign = element[element.Length-1];
                    metaBlockDictionary.Add(sign, type);
                }
            }
            return metaBlockDictionary;
        }
        
        /// <summary>
        /// Finds the time for the timer in metadata
        /// </summary>
        /// <param name="fileName">current level</param>
        /// <returns>Timer value</returns>
        public int MetaReaderTimer (string fileName) {
            int time = 0;
            foreach (string element in levelData.Meta(fileName)) {
                if (element.Substring(0, element.IndexOf(':')) == "Time") {
                    time = Int32.Parse(element.Substring(element.LastIndexOf(':') + 2));
                }
            }
            return time;
        }
    }
}