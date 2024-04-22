using DIKUArcade.Entities;
using DIKUArcade.Math;
using Breakout.Factories;

namespace Breakout.Gameinfo { 
    public class LivesCreator {
        private CentralFactory factory = new CentralFactory();

        /// <summary>
        /// Creates an EntityCOntainer with the different numbers by seperating an int into digits
        /// and then assigning an image to each digits and adding them to the EntityContainer
        /// </summary>
        /// <param name="value">int value that needs to be converted</param>
        /// <param name="numbers">EntityContainer for the numbers</param>
        /// <param name="Position">Position for the numbers</param>
        /// <returns> An EntityContainer of Entities </returns>
        public EntityContainer<Entity> Numbers(int value, EntityContainer<Entity> numbers, Vec2F Position) {
            numbers.ClearContainer ();
            float Xposition = Position.X;
            for (int i = 0; i < value; i++) {
                Xposition = Xposition + 0.05f;
                Position = new Vec2F (Xposition, Position.Y);
                numbers.AddEntity ((factory.Build(new Vec2F(Xposition, Position.Y), "Lives")));
            }
            return numbers;   
        }
    }
}