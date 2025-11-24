<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **JAVA NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 FILE HANDLING

♦️ **FILE CLASS**
File represents names of the files/directories, not their contents.

```java
File f1 = new File("data.txt");                       // relative path
File f2 = new File("C:/Users/abc/Desktop/data.txt"); // absolute path
File f3 = new File("folder", "data.txt");            // parent + child
```

IMPORTENT CHECKS :
`f.exists();`
`f.isFile();`
`f.isDirectory();`
`f.canRead();`
`f.canWrite();`
`f.canExecute();`

METADATA
`f.length();` // in bytes
`f.getName();`
`f.getParent();`
`f.getAbsolutePath();`
`f.lastModified();`

OPERATIONS
`f.createNewFile();`
`f.mkdir();` // one directory
`f.mkdirs();` // nested directories
`f.delete();`

> 📝 NOTE : File class cannot read/write data, only handles metadata & paths.



</div>
</div>
