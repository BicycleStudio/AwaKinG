using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AwaKinG.src.core.engine;

namespace AwaKinG.src.core
{
    public class Engine : IEngine
    {
        List<Entity> Entities = new List<Entity>();
        public Engine()
        {

        }
        public bool Initialize()
        {
            return true;
        }
        public void Shutdown()
        {
            foreach (Entity ent in Entities)
                ent.Shutdown();
        }
        public void Update()
        {
            foreach (Entity ent in Entities)
                ent.Update();
        }
    }
}
