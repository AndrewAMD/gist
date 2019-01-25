 var LibraryPrintNumbers = {
  // These are empty, designed to be replaced when a debugger is invoked
  print_numbers: function(a,b,c) {
	console.log(a);
    console.log(b);
    console.log(c);
  },
};

mergeInto(LibraryManager.library, LibraryPrintNumbers);