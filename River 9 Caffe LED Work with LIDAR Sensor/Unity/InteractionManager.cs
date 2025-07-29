using UnityEngine;

public class InteractionManager : MonoBehaviour
{
    public float InteractionPower = 10.0f;

    void Awake()
    {

    }

    void Start()
    {
        
    }

    void Update()
    {
        if (Input.mousePositionDelta.magnitude > 1.0f)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if (Physics.Raycast(ray, out hit))
            {
                if (hit.collider.gameObject.CompareTag("Interaction Object"))
                {
                    hit.collider.gameObject.GetComponentInParent<SpawnObject>().InteractionObject(InteractionPower);
                }
            }
        }
    }
}
