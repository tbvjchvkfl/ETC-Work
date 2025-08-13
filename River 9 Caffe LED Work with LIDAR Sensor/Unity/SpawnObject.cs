using UnityEngine;

public class SpawnObject : MonoBehaviour
{
    public float MoveSpeed = 0.0001f;
    public GameObject SpawnArea;
    
    CharacterController controller;
    BoxCollider clampMovingArea;

    void Awake()
    {
        controller = GetComponent<CharacterController>();
        if (SpawnArea)
        {
            clampMovingArea = SpawnArea.GetComponent<BoxCollider>();
        }
    }

    void Update()
    {
    }

    public void InteractionObject(float Power)
    {
        /*if (Obj_RigidBody)
        {a
            Vector3 RandomDirection = new Vector3(Random.Range(-1f, 1f), Random.Range(0f, 1f), Random.Range(-1f, 1f)).normalized;
            Obj_RigidBody.AddForce(RandomDirection * Power, ForceMode.Impulse);
            Debug.Log("Object Interacted");
        }*/
    }

    public void Move()
    {
        controller.Move(transform.forward * MoveSpeed * Time.deltaTime);
        Rotation();
    }

    void Rotation()
    {

    }
}
