using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using System.IO;
using System;

namespace Breakout.EntityData.Blocks {
    public class TeleportingBlock : Block {
        private int hitpoints;
        private string Name;
        private Random rand = new Random();
        public override int GetHitpoints {
            get {return hitpoints;}
        }
        
        public TeleportingBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 2;
            Image = image;
            Name = name;
        }
        
        /// <summary>
        /// Detects the amount of hitpoints and sets damaged Image when at 1, triggers teleport special effect
        /// </summary>
        public override void Hit (EntityContainer<Block> blocks) {
            hitpoints--;
            SpecialEffect();
            if (hitpoints == 1) {
                Image = new Image(Path.Combine("Assets", "Images", Name.Insert(Name.IndexOf(".png"), "-damaged")));
            } else if (hitpoints == 0) {
                this.DeleteEntity();
            }
        }
        
        /// <summary>
        /// Teleports the block to a random location on the board
        /// </summary>
        public override void SpecialEffect () {
            float PositionX = rand.Next(1, 100);
            float PositionY = rand.Next(20, 95);
            Shape.Position.X = PositionX/100;
            Shape.Position.Y = PositionY/100;
        }
    }
}