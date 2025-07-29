using UnityEngine;

public class SpawnObject : MonoBehaviour
{
    public Rigidbody Obj_RigidBody;

    void Awake()
    {
    }
    
    void Update()
    {
        
    }

    public void InteractionObject(float Power)
    {
        Debug.Log("Interaction");
        if (Obj_RigidBody)
        {
            Vector3 RandomDirection = new Vector3(Random.Range(-1f, 1f), Random.Range(0f, 1f), Random.Range(-1f, 1f)).normalized;
            Obj_RigidBody.AddForce(RandomDirection * Power, ForceMode.Impulse);
            Debug.Log("Object Interacted");
        }
    }
}
