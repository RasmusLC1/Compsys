using DIKUArcade.Graphics;
using DIKUArcade.Entities;

namespace Breakout.EntityData.Blocks {
    public abstract class Block : Entity {
        private int hitpoints;
        private string Name;
        public virtual int GetHitpoints {
            get {return hitpoints;}
        }
        public string GetName {
            get {return Name;}
        }
        
        public Block (StationaryShape shape, IBaseImage image, string name) : base(shape, image) {
            hitpoints = 1;
            this.Image = image;
            this.Name = name;
        }

        /// <summary>
        /// Method to apply a hit to a block which triggers a special effect
        /// </summary>
        public abstract void Hit (EntityContainer<Block> blocks);

        /// <summary>
        /// Moves the block based on the speedmodifier
        /// </summary>
        /// <param name="speedmodifier">Ball count to keep speed stable</param>
        public virtual void Move (int speedmodifier) {}
        
        /// <summary>
        /// Special effects for blocks that can be triggered by hit
        /// </summary>
        public virtual void SpecialEffect () {}
    }
}