using DIKUArcade.Entities;
using DIKUArcade.Math;
using System;
using System.Collections.Generic;
using Breakout.EntityData.Blocks;
using Breakout.EntityData.PowerUps;
using Breakout.Factories;

namespace Breakout.Levels { 
    public class LevelBuilder {
        private static LevelBuilder instance = null;
        private EntityContainer<Block> blocks = new EntityContainer<Block> ();
        private Map map = new Map ();
        private Meta meta = new Meta ();
        private BlockFactory blockConstructor = new BlockFactory();
        private PowerUpFactory powerUpConstructor = new PowerUpFactory();
        private Legend legend = new Legend ();
        private Block block;
        private List<Tuple<Vec2F,char>> MapList = new List<Tuple<Vec2F,char>> ();
        List<Tuple<string,char>> LegenList = new List<Tuple<string,char>> ();
        private List<string> powerups = new List<string>();
        private TextFileReader textconverter = new TextFileReader();
        private Dictionary<char, string> metaBlockDictionary = new Dictionary<char, string> ();
        private EntityContainer <PowerUp> powerUps = new EntityContainer<PowerUp>();
        public EntityContainer<Block> GetBlocks {
            get {return blocks;}
        }
        public EntityContainer<PowerUp> GetPowerUps {
            get {return powerUps;}
        }
        public Dictionary<char, string> GetMeta {
            get {return metaBlockDictionary;}
        }

        /// <summary>
        /// Sets the GameRunning to the current instance
        /// </summary>
        /// <returns>GameRunning instance</returns>
        public static LevelBuilder GetInstance() {
            if (LevelBuilder.instance == null) {
                LevelBuilder.instance = new LevelBuilder();
            }
            return LevelBuilder.instance;
        }

        /// <summary>
        /// Creates Breakout level and acts as the gathering point for the other methods
        /// and creates a PowerUp if there is a PowerUpBlock
        /// </summary>
        /// <param name="level"> The level of type string </param>
        public void LevelCreator (string level) {
            ClearLevel();
            GetData(level);
            for (int i = 0; i < MapList.Count; i++) {
                for (int j = 0; j < LegenList.Count; j++) {
                    if (MapList[i].Item2 == LegenList[j].Item2) {
                        block = blockConstructor.BlockBuilder(LegenList[j].Item1, LegenList[j].Item2,
                        MapList[i].Item1, metaBlockDictionary); 
                        blocks.AddEntity(block);
                        if (block is PowerUpBlock) {
                           powerUpConstructor.PowerUpBuilder(block, powerUps, powerups);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Extracts the data from the level file and stores it in the lists used in the other methods
        /// </summary>
        /// <param name="level">current level</param>
        private void GetData(string level) {
            MapList = map.MapReader (level);
            metaBlockDictionary = meta.MetaReaderBlocks(level);
            powerups = textconverter.FileReader("Powerups");
            LegenList = legend.LegendReader(level);
        }

        /// <summary>
        /// Clears the levelData.
        /// </summary>
        public void ClearLevel() {
            blocks.ClearContainer();
            powerUps.ClearContainer();
            MapList.Clear();
        }
        
        /// <summary>
        /// Renders the entities
        /// </summary>
        public void Render() {
            blocks.RenderEntities();
            powerUps.RenderEntities();
        }
    }
}