using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using Breakout.Gameinfo;

namespace Breakout.EntityData.Blocks {
    public class UnbreakableBlock : Block {
        private int hitpoints;
        private string Name;
        private GameValues values = GameValues.GetInstance();
        public override int GetHitpoints {
            get {return hitpoints;}
        }
        
        public UnbreakableBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 1;
            Image = image;
            Name = name;
        }
        
        /// <summary>
        /// Does nothing as they block is unbreakable
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {}
        
        /// <summary>
        /// Deletes the block if triggered
        /// </summary>
        public override void SpecialEffect () {
            DeleteEntity();
            values.UpdateScore();
            
        }
    }
}