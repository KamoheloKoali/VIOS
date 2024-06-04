import NavBar from "./NavBar"
import './AddContact.css'


const AddContact = () => {
  return (
    <>
      <h3>Add Contact</h3>
      
      <div class='input' id="inputs">
        <input type="text" placeholder="Name" />
        <input type="number" placeholder="Phone number" />
        <input type="text" placeholder="Category" />
        <div id="button"><button>ADD</button></div>
      </div>
      
      
    </>
  )
}


export default AddContact
