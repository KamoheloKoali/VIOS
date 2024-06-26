import { SignedIn, SignedOut, SignInButton, UserButton } from "@clerk/clerk-react";

let reloadCount = sessionStorage.getItem('reloadCount');
  reloadCount = reloadCount ? parseInt(reloadCount) : 0; // Convert to number or default to 0

  // if (reloadCount < 1) {
  //   reloadCount++; // Increment reloadCount
  //   sessionStorage.setItem('reloadCount', String(reloadCount)); // Store updated value

  //   window.location.reload(); // Reload the page
  // } else {
  //   sessionStorage.removeItem('reloadCount'); // Remove reloadCount if limit reached
  // }

const Profile = () => {
    
  return (
    <div style={styles.container}>
      <header style={styles.header}>
        <h1 style={styles.title}>Profile</h1>
      </header>
      <div style={styles.profileImageContainer}>
        <UserButton />
        <button style={styles.editButton}>Edit profile image</button>
      </div>
      <div style={styles.infoContainer}>
        <ProfileInfo label="Name" value="Tumelo Nkoe" />
        <ProfileInfo label="Username" value="Tumelo003" />
        <ProfileInfo label="Email" value="nkoetumelo03@gmail" />
        <ProfileLinks label="Links" links={['website.net', 'mylink.net', 'yourlink.net']} />
        <ProfileInfo label="Bio" value="Front-end developer." />
      </div>
    </div>
  );
};

const ProfileInfo = ({ label, value }) => {
  return (
    <div style={styles.infoRow}>
      <span>{label}</span>
      <span>{value}</span>
    </div>
  );
};

const ProfileLinks = ({ label, links }) => {
  return (
    <div style={styles.infoRow}>
      <span>{label}</span>
      <div style={styles.linksContainer}>
        {links.map((link, index) => (
          <span key={index} style={styles.link}>{link}</span>
        ))}
        <button style={styles.addLinkButton}>+ Add link</button>
      </div>
    </div>
  );
};

const styles = {
  container: {
    padding: '20px',
    fontFamily: 'Arial, sans-serif',
  },
  header: {
    display: 'flex',
    alignItems: 'center',
    borderBottom: '1px solid #ddd',
    paddingBottom: '10px',
    marginBottom: '20px',
  },
  title: {
    fontSize: '24px',
    margin: 0,
    
  },
  profileImageContainer: {
    textAlign: 'center',
    marginBottom: '20px',
  },
  profileImage: {
    width: '100px',
    height: '100px',
    borderRadius: '50%',
  },
  editButton: {
    borderRadius: '3px',
    border: 'none',
    backgroundColor: 'black',
    color: 'ghostwhite',
    display: 'block',
    margin: '10px auto',
    padding: '5px 10px',
    fontSize: '14px',
    cursor: 'pointer',
  },
  infoContainer: {
    borderTop: '1px solid #ddd',
    paddingTop: '10px',
  },
  infoRow: {
    display: 'flex',
    justifyContent: 'space-between',
    margin: '10px 0',
  },
  linksContainer: {
    display: 'flex',
    flexDirection: 'column',
  },
  link: {
    marginBottom: '5px',
  },
  addLinkButton: {
    border: 'none',
    backgroundColor: 'black',
    color: 'ghostwhite',
    padding: '5px 10px',
    fontSize: '14px',
    cursor: 'pointer',
  },
};


export default Profile;
