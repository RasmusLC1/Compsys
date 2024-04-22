using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using System;
using System.Collections.Generic;
using Breakout.EntityData.Blocks;

namespace Breakout.Factories { 
    public class BlockFactory {
        private Block block;

        /// <summary>
        /// Creates the blocks themselves on a designated position, type and colour matching that of the levelfile
        /// </summary>
        /// <param name="blockname">name of block</param>
        /// <param name="LegendKey">the key of the block</param>
        /// <param name="blockPosition">position of block</param>
        /// <returns> A block </returns>
        public Block BlockBuilder(string blockname, char LegendKey, Vec2F blockPosition,
        Dictionary<char, string> metaBlockDictionary) {        
            Type Blocktype = Type.GetType("Breakout.EntityData.Blocks.DefaultBlock");
            if (metaBlockDictionary.ContainsKey(LegendKey)) {
                Blocktype = Type.GetType("Breakout.EntityData.Blocks." + metaBlockDictionary[LegendKey] + "Block");
            }
            block = (Block)Activator.CreateInstance(Blocktype,     
                new StationaryShape(blockPosition, new Vec2F(0.083f, 0.04f)),
                new Image(Path.Combine("Assets", "Images", blockname)),
                blockname);
            return block;
        }
    }
}