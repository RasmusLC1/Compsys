using DIKUArcade.Entities;
using DIKUArcade.Math;
using System;
using Breakout.EntityData.EntityLogic;

namespace Breakout.Factories {
    public class CentralFactory {
        EntityContainer<Ball> balls = new EntityContainer<Ball>();
        private IFactory factory;

        /// <summary>
        /// Distributes the EntityCreation to differen factories
        /// </summary>
        /// <param name="Position">Position of new entity</param>
        /// <param name="type">Type of Entity</param>
        /// <returns></returns>
        public Entity Build (Vec2F Position, string type) {
            Type FactoryType = null;
            FactoryType = Type.GetType("Breakout.Factories." + type + "Factory");
            factory = (IFactory)Activator.CreateInstance(FactoryType);
            Entity entity = factory.Build(Position);
            return entity;
        }
    }
}