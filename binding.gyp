{
  'targets': [
    {
      'target_name': 'divsufsort',
      'sources': [ 
        'src/divsufsort.cc' 
      ],
      'libraries': [
        '-ldivsufsort',
        '-L/usr/lib',
        '-L/usr/local/lib'
      ],
    }
  ]
}
